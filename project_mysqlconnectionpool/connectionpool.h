#pragma once
#include<string>
#include<queue>
#include<mutex>
#include"connection.h"
#include"connection_mysql.h"
#include<atomic>	//原子操作
#include<memory>	//智能指针
#include<thread>
#include<condition_variable>	//条件变量，用来同步操作
#include<functional>			//使用其中的绑定函数bind()


//实现连接池功能模块,使用单例模式
class ConnectionPool {
public:
	static ConnectionPool* getConnectionPool();

	//消费者线程消费连接
	shared_ptr<Connection> getConnection();	

private:
	//单例模式，构造函数私有化
	ConnectionPool();

	//子线程的入口函数
	void produceConnectionTask();

	//回收超时的连接
	void scannerConnectionTask();

	//从配置文件中加载配置项
	bool loadConfigFile();

	string _ip;				//mysql的ip地址
	unsigned short _port;	//端口号
	string _username;		//用户名
	string _password;		//登录密码
	string _dbname;			//连接的数据库名称
	int _initSize;			//连接池的初始连接量
	int _maxSize;			//连接池的最大连接量
	int _maxIdleTime;		//连接池的最大空闲时间s
	int _connectionTimeout;	//连接池获取连接的超时时间ms

	queue<Connection*> _connectionQue;	//连接池的连接队列
	mutex _queueMutex;					//维护连接队列的线程安全互斥锁
	atomic_int _connectionCnt;			//记录连接所创建的connection连接的总数量
	condition_variable cv;				//设置条件变量，用于连接生产线程和连接消费线程的通信
};