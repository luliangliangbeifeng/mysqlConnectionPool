#pragma once
#include <string>
#include<ctime>
#include "mysql.h"
using namespace std;

//抽象类，方便后期拓展
class Connection {
public:
	//初始化数据库连接
	Connection() {}
	//释放数据库连接
	virtual ~Connection() {}
	//连接数据库, 其中包括ip地址，port端口号，用户名，密码， 数据库名称
	virtual bool connect(string ip, unsigned short port, string user, string password, string dbname) = 0;
	//更新数据库操作
	virtual bool update(string sql) = 0;
	//查询操作
	virtual bool search(string sql) = 0;

	//刷新一下连接的起始空闲时间
	void refreshAliveTime() { alivetime = clock(); }
	//返回存活时间
	clock_t getAliveTime() const { return clock() - alivetime; }

	clock_t alivetime;	//记录进入空闲状态后的起始存活时间
};