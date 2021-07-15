#pragma once
#include<iostream>
#include "connection.h"

//MySQL��
class Connection_mysql :public Connection {
public:
	//��ʼ�����ݿ�����
	Connection_mysql();
	//�ͷ����ݿ�����
	virtual ~Connection_mysql();
	//�������ݿ�, ip��ַ��port�˿ںţ��û��������룬 ���ݿ�����
	virtual bool connect(string ip, unsigned short port, string user, string password, string dbname);
	//�������ݿ����
	virtual bool update(string sql);
	//��ѯ����
	virtual bool search(string sql);

private:
	MYSQL* _con;		//��ʾ��MySQL Server��һ������	
	
};
