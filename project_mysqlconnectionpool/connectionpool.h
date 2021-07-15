#pragma once
#include<string>
#include<queue>
#include<mutex>
#include"connection.h"
#include"connection_mysql.h"
#include<atomic>	//ԭ�Ӳ���
#include<memory>	//����ָ��
#include<thread>
#include<condition_variable>	//��������������ͬ������
#include<functional>			//ʹ�����еİ󶨺���bind()


//ʵ�����ӳع���ģ��,ʹ�õ���ģʽ
class ConnectionPool {
public:
	static ConnectionPool* getConnectionPool();

	//�������߳���������
	shared_ptr<Connection> getConnection();	

private:
	//����ģʽ�����캯��˽�л�
	ConnectionPool();

	//���̵߳���ں���
	void produceConnectionTask();

	//���ճ�ʱ������
	void scannerConnectionTask();

	//�������ļ��м���������
	bool loadConfigFile();

	string _ip;				//mysql��ip��ַ
	unsigned short _port;	//�˿ں�
	string _username;		//�û���
	string _password;		//��¼����
	string _dbname;			//���ӵ����ݿ�����
	int _initSize;			//���ӳصĳ�ʼ������
	int _maxSize;			//���ӳص����������
	int _maxIdleTime;		//���ӳص�������ʱ��s
	int _connectionTimeout;	//���ӳػ�ȡ���ӵĳ�ʱʱ��ms

	queue<Connection*> _connectionQue;	//���ӳص����Ӷ���
	mutex _queueMutex;					//ά�����Ӷ��е��̰߳�ȫ������
	atomic_int _connectionCnt;			//��¼������������connection���ӵ�������
	condition_variable cv;				//���������������������������̺߳����������̵߳�ͨ��
};