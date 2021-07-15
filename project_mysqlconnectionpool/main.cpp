#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"connectionpool.h"
//定义N则使用多线程，没有定义则使用单线程
#define N
//单线程连接次数
//使用连接池标志位，1表示使用连接池，0表示不使用
bool flag_connectionpool = false;
#define num_single  300
//多线程连接次数
#define num_mult    10000

using namespace std;

int main()
{
	//获得单例模式的连接池对象
	ConnectionPool* cp = ConnectionPool::getConnectionPool();

#ifdef N
	clock_t begin = clock();
	thread t1([&]() {
		for (int i = 0; i < num_mult / 8; i++) {
			if (!flag_connectionpool) {
				//不使用连接池
				shared_ptr<Connection> con(new Connection_mysql());
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai1", 23, "man");
				con->connect("127.0.0.1", 3306, "root", "root", "mysql");		//连接数据库
				con->update(sql);
			}
			else {
				//使用连接池
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai2", 12, "female");
				shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
				sp->update(sql);
			}
		}
	});

	thread t2([&]() {
		for (int i = 0; i < num_mult / 8; i++) {
			if (!flag_connectionpool) {
				//不使用连接池
				shared_ptr<Connection> con(new Connection_mysql());
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai1", 23, "man");
				con->connect("127.0.0.1", 3306, "root", "root", "mysql");		//连接数据库
				con->update(sql);
			}
			else {
				//使用连接池
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai2", 12, "female");
				shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
				sp->update(sql);
			}
		}
	});

	thread t3([&]() {
		for (int i = 0; i < num_mult / 8; i++) {
			if (!flag_connectionpool) {
				//不使用连接池
				shared_ptr<Connection> con(new Connection_mysql());
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai1", 23, "man");
				con->connect("127.0.0.1", 3306, "root", "root", "mysql");		//连接数据库
				con->update(sql);
			}
			else {
				//使用连接池
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai2", 12, "female");
				shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
				sp->update(sql);
			}
		}
	});

	thread t4([&]() {
		for (int i = 0; i < num_mult / 8; i++) {
			if (!flag_connectionpool) {
				//不使用连接池
				shared_ptr<Connection> con(new Connection_mysql());
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai1", 23, "man");
				con->connect("127.0.0.1", 3306, "root", "root", "mysql");		//连接数据库
				con->update(sql);
			}
			else {
				//使用连接池
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai2", 12, "female");
				shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
				sp->update(sql);
			}
		}
	});

	thread t5([&]() {
		for (int i = 0; i < num_mult / 8; i++) {
			if (!flag_connectionpool) {
				//不使用连接池
				shared_ptr<Connection> con(new Connection_mysql());
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai1", 23, "man");
				con->connect("127.0.0.1", 3306, "root", "root", "mysql");		//连接数据库
				con->update(sql);
			}
			else {
				//使用连接池
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai2", 12, "female");
				shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
				sp->update(sql);
			}
		}
	});

	thread t6([&]() {
		for (int i = 0; i < num_mult / 8; i++) {
			if (!flag_connectionpool) {
				//不使用连接池
				shared_ptr<Connection> con(new Connection_mysql());
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai1", 23, "man");
				con->connect("127.0.0.1", 3306, "root", "root", "mysql");		//连接数据库
				con->update(sql);
			}
			else {
				//使用连接池
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai2", 12, "female");
				shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
				sp->update(sql);
			}

		}
	});

	thread t7([&]() {
		for (int i = 0; i < num_mult / 8; i++) {
			if (!flag_connectionpool) {
				//不使用连接池
				shared_ptr<Connection> con(new Connection_mysql());
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai1", 23, "man");
				con->connect("127.0.0.1", 3306, "root", "root", "mysql");		//连接数据库
				con->update(sql);
			}
			else {
				//使用连接池
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai2", 12, "female");
				shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
				sp->update(sql);
			}
		}
	});
	thread t8([&]() {
		for (int i = 0; i < num_mult / 8; i++) {
			if (!flag_connectionpool) {
				//不使用连接池
				shared_ptr<Connection> con(new Connection_mysql());
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai1", 23, "man");
				con->connect("127.0.0.1", 3306, "root", "root", "mysql");		//连接数据库
				con->update(sql);
			}
			else {
				//使用连接池
				char sql[1024] = { 0 };											//初始化为空
				sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai2", 12, "female");
				shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
				sp->update(sql);
			}
		}
	});

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	cout << "使用八线程连接" << num_mult << "次，共用时间:   " << clock() - begin << "ms" << endl;
#else
	clock_t begin = clock();
	for (int i = 0; i < num_single; i++) {		
		if (!flag_connectionpool) {
			//不使用连接池
			shared_ptr<Connection> con(new Connection_mysql());
			char sql[1024] = { 0 };	
			sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai1", 23, "man");
			con->connect("127.0.0.1", 3306, "root", "root", "mysql");		//连接数据库
			con->update(sql);
		}
		else {
			//使用连接池
			char sql[1024] = { 0 };	
			sprintf(sql, "insert into person(name, age, sex) values('%s', '%d', '%s')", "huatai2", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();
			sp->update(sql);
		}		
	}
	cout << "使用单线程连接" << num_single << "次，共用时间:   " << clock() - begin << "ms" << endl;
#endif
	system("pause");
	return 0;
}