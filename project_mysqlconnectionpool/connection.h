#pragma once
#include <string>
#include<ctime>
#include "mysql.h"
using namespace std;

//�����࣬���������չ
class Connection {
public:
	//��ʼ�����ݿ�����
	Connection() {}
	//�ͷ����ݿ�����
	virtual ~Connection() {}
	//�������ݿ�, ���а���ip��ַ��port�˿ںţ��û��������룬 ���ݿ�����
	virtual bool connect(string ip, unsigned short port, string user, string password, string dbname) = 0;
	//�������ݿ����
	virtual bool update(string sql) = 0;
	//��ѯ����
	virtual bool search(string sql) = 0;

	//ˢ��һ�����ӵ���ʼ����ʱ��
	void refreshAliveTime() { alivetime = clock(); }
	//���ش��ʱ��
	clock_t getAliveTime() const { return clock() - alivetime; }

	clock_t alivetime;	//��¼�������״̬�����ʼ���ʱ��
};