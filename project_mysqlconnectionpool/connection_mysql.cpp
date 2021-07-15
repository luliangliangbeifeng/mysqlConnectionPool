#include "connection_mysql.h"

Connection_mysql::Connection_mysql() {
	//初始化数据库连接
	_con = mysql_init(nullptr);	
}

Connection_mysql::~Connection_mysql() {
	//释放数据库连接资源
	if (_con != nullptr) {
		mysql_close(_con);
	}
}

bool Connection_mysql::connect(string ip, unsigned short port, string username, string password, string dbname) {
	//连接数据库
	MYSQL* p = mysql_real_connect(_con, ip.c_str(), username.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
	if (p == nullptr) { cout << "123" << endl; }
	return p != nullptr;			//p为空则连接失败，不为空则连接成功
}

bool Connection_mysql::update(string sql) {
	//更新操作,insert,delete,update
	if (mysql_query(_con, sql.c_str())) {
		cout << "数据更新失败：" << sql << endl;
		return false;
	} 
	return true;
}

bool Connection_mysql::search(string sql) {
	//查询操作,mysql_query()函数执行成功则返回0
	if (mysql_query(_con, sql.c_str())) {
		cout << "数据查找失败：" << sql << endl;
		return false;
	}
	return true;
}