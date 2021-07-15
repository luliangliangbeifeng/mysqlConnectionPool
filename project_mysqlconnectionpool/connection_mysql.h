#pragma once
#include<iostream>
#include "connection.h"

//MySQL类
class Connection_mysql :public Connection {
public:
	//初始化数据库连接
	Connection_mysql();
	//释放数据库连接
	virtual ~Connection_mysql();
	//连接数据库, ip地址，port端口号，用户名，密码， 数据库名称
	virtual bool connect(string ip, unsigned short port, string user, string password, string dbname);
	//更新数据库操作
	virtual bool update(string sql);
	//查询操作
	virtual bool search(string sql);

private:
	MYSQL* _con;		//表示和MySQL Server的一条连接	
	
};
