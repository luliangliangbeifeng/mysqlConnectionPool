#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "connectionpool.h"

using namespace std;

ConnectionPool::ConnectionPool() {
	//加载mysql.ini中的基本配置
	if (!loadConfigFile()) { return; }							//若加载错误，直接返回

	//创建初始数量的连接
	for (int i = 0; i < _initSize; i++) {
		Connection* p = new Connection_mysql();						//创建一个连接对象
		p->connect(_ip, _port, _username, _password, _dbname);	//将此对象连接到数据库
		p->refreshAliveTime();									//更新此连接的空闲存活起始时间				
		_connectionQue.push(p);									//将此连接放入队列
		_connectionCnt++;										//当前连接数量加一
	}

	//生产者线程
	thread produce(&ConnectionPool::produceConnectionTask, this);
	produce.detach();

	//启动一个新的定时线程，扫描超过maxIdleTime时间的空闲连接，回收超时连接
	thread scanner(std::bind(&ConnectionPool::scannerConnectionTask, this));
	scanner.detach();
}

//消费者线程
shared_ptr<Connection> ConnectionPool::getConnection() {
	unique_lock<mutex> lock(_queueMutex);		//加锁
	while (_connectionQue.empty()) {
		if (cv.wait_for(lock, chrono::milliseconds(_connectionTimeout)) == cv_status::timeout) {
			if (_connectionQue.empty()) {
				cout <<"获取空闲连接超时。。。。获取连接失败！" << endl;
				return nullptr;
			}
		}
	}
	//队列不为空，获取连接队列中的最前面一个connection
	shared_ptr<Connection> sp(_connectionQue.front(),
		[&](Connection* pcon) {
			unique_lock<mutex> lock(_queueMutex);
			pcon->refreshAliveTime();
			_connectionQue.push(pcon); }
	);
	_connectionQue.pop();
	cv.notify_all();				
	return sp;
}

//produce生产者线程的入口函数
void ConnectionPool::produceConnectionTask() {
	while (true) {
		unique_lock<mutex> lock(_queueMutex);	
		while (!_connectionQue.empty()) {
			cv.wait(lock);						
		}
		//当前存在的连接数量小于最大连接数量，允许生产
		if (_connectionCnt < _maxSize) {
			Connection* p = new Connection_mysql();	
			p->connect(_ip, _port, _username, _password, _dbname);
			p->refreshAliveTime();									
			_connectionQue.push(p);									
			_connectionCnt++;										
		}
		//通知各消费者线程，可以消费连接
		cv.notify_all();
	}
}

//scanner扫描线程的入口函数
void ConnectionPool::scannerConnectionTask() {
	while (true) {
		//通过sleep模拟定时效果
		this_thread::sleep_for(chrono::seconds(_maxIdleTime));
		//扫描整个队列，释放多余的连接
		unique_lock<mutex> lock(_queueMutex);
		while (_connectionCnt > _initSize) {
			Connection* p = _connectionQue.front();
			if (p->getAliveTime() >= (_maxIdleTime * 1000)) {
				_connectionQue.pop();
				_connectionCnt--;
				delete p;	
			}
			else {
				break;						//第一个不超过，那么后面的都不会超过
			}
		}

	}
}

//从配置文件中加载配置项
bool ConnectionPool::loadConfigFile() {
	FILE* pf = fopen("mysql.ini", "r");				
	if (pf == nullptr) {
		cout << "mysql.ini文件打开失败" << endl;
		return false;
	}
	while (!feof(pf)) {
		char line[1024] = { 0 };					
		fgets(line, 1024, pf);
		string str = line;
		int idx = str.find('=', 0);					//默认从起始位置开始查找
		if (idx == -1) {			
			continue;
		}
		int endidx = str.find('\n', idx);
		string key = str.substr(0, idx);
		string value = str.substr(idx + 1, endidx - idx - 1);

		if (key == "ip") {
			_ip = value;
		}
		else if (key == "port") {
			_port = atoi(value.c_str());
		}
		else if (key == "username") {
			_username = value;
		}
		else if (key == "password") {
			_password = value;
		}
		else if (key == "dbname")
		{
			_dbname = value;
		}
		else if (key == "initSize")
		{
			_initSize = atoi(value.c_str());
		}
		else if (key == "maxSize")
		{
			_maxSize = atoi(value.c_str());
		}
		else if (key == "maxIdleTime")
		{
			_maxIdleTime = atoi(value.c_str());
		}
		else if (key == "connectionTimeOut")
		{
			_connectionTimeout = atoi(value.c_str());
		}
	}
	return true;
}

//单例函数接口
ConnectionPool* ConnectionPool::getConnectionPool() {
	static ConnectionPool pool;
	return &pool;
}