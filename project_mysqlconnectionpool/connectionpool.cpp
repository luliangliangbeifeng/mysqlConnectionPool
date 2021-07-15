#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "connectionpool.h"

using namespace std;

ConnectionPool::ConnectionPool() {
	//����mysql.ini�еĻ�������
	if (!loadConfigFile()) { return; }							//�����ش���ֱ�ӷ���

	//������ʼ����������
	for (int i = 0; i < _initSize; i++) {
		Connection* p = new Connection_mysql();						//����һ�����Ӷ���
		p->connect(_ip, _port, _username, _password, _dbname);	//���˶������ӵ����ݿ�
		p->refreshAliveTime();									//���´����ӵĿ��д����ʼʱ��				
		_connectionQue.push(p);									//�������ӷ������
		_connectionCnt++;										//��ǰ����������һ
	}

	//�������߳�
	thread produce(&ConnectionPool::produceConnectionTask, this);
	produce.detach();

	//����һ���µĶ�ʱ�̣߳�ɨ�賬��maxIdleTimeʱ��Ŀ������ӣ����ճ�ʱ����
	thread scanner(std::bind(&ConnectionPool::scannerConnectionTask, this));
	scanner.detach();
}

//�������߳�
shared_ptr<Connection> ConnectionPool::getConnection() {
	unique_lock<mutex> lock(_queueMutex);		//����
	while (_connectionQue.empty()) {
		if (cv.wait_for(lock, chrono::milliseconds(_connectionTimeout)) == cv_status::timeout) {
			if (_connectionQue.empty()) {
				cout <<"��ȡ�������ӳ�ʱ����������ȡ����ʧ�ܣ�" << endl;
				return nullptr;
			}
		}
	}
	//���в�Ϊ�գ���ȡ���Ӷ����е���ǰ��һ��connection
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

//produce�������̵߳���ں���
void ConnectionPool::produceConnectionTask() {
	while (true) {
		unique_lock<mutex> lock(_queueMutex);	
		while (!_connectionQue.empty()) {
			cv.wait(lock);						
		}
		//��ǰ���ڵ���������С�����������������������
		if (_connectionCnt < _maxSize) {
			Connection* p = new Connection_mysql();	
			p->connect(_ip, _port, _username, _password, _dbname);
			p->refreshAliveTime();									
			_connectionQue.push(p);									
			_connectionCnt++;										
		}
		//֪ͨ���������̣߳�������������
		cv.notify_all();
	}
}

//scannerɨ���̵߳���ں���
void ConnectionPool::scannerConnectionTask() {
	while (true) {
		//ͨ��sleepģ�ⶨʱЧ��
		this_thread::sleep_for(chrono::seconds(_maxIdleTime));
		//ɨ���������У��ͷŶ��������
		unique_lock<mutex> lock(_queueMutex);
		while (_connectionCnt > _initSize) {
			Connection* p = _connectionQue.front();
			if (p->getAliveTime() >= (_maxIdleTime * 1000)) {
				_connectionQue.pop();
				_connectionCnt--;
				delete p;	
			}
			else {
				break;						//��һ������������ô����Ķ����ᳬ��
			}
		}

	}
}

//�������ļ��м���������
bool ConnectionPool::loadConfigFile() {
	FILE* pf = fopen("mysql.ini", "r");				
	if (pf == nullptr) {
		cout << "mysql.ini�ļ���ʧ��" << endl;
		return false;
	}
	while (!feof(pf)) {
		char line[1024] = { 0 };					
		fgets(line, 1024, pf);
		string str = line;
		int idx = str.find('=', 0);					//Ĭ�ϴ���ʼλ�ÿ�ʼ����
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

//���������ӿ�
ConnectionPool* ConnectionPool::getConnectionPool() {
	static ConnectionPool pool;
	return &pool;
}