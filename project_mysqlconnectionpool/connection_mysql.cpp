#include "connection_mysql.h"

Connection_mysql::Connection_mysql() {
	//��ʼ�����ݿ�����
	_con = mysql_init(nullptr);	
}

Connection_mysql::~Connection_mysql() {
	//�ͷ����ݿ�������Դ
	if (_con != nullptr) {
		mysql_close(_con);
	}
}

bool Connection_mysql::connect(string ip, unsigned short port, string username, string password, string dbname) {
	//�������ݿ�
	MYSQL* p = mysql_real_connect(_con, ip.c_str(), username.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
	if (p == nullptr) { cout << "123" << endl; }
	return p != nullptr;			//pΪ��������ʧ�ܣ���Ϊ�������ӳɹ�
}

bool Connection_mysql::update(string sql) {
	//���²���,insert,delete,update
	if (mysql_query(_con, sql.c_str())) {
		cout << "���ݸ���ʧ�ܣ�" << sql << endl;
		return false;
	} 
	return true;
}

bool Connection_mysql::search(string sql) {
	//��ѯ����,mysql_query()����ִ�гɹ��򷵻�0
	if (mysql_query(_con, sql.c_str())) {
		cout << "���ݲ���ʧ�ܣ�" << sql << endl;
		return false;
	}
	return true;
}