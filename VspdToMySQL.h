#ifndef VSPDTOMYSQL
#define VSPDTOMYSQL

////////////////////////////////////////////////////////////////////////////////////////////////
//把SQL操作封装成一个类
#include <iostream>
#include <cstring>
#include <string>
#include <mysql.h>
using namespace std;
class VspdToMySQL
{
public:
	VspdToMySQL();
	~VspdToMySQL();
	MYSQL mysql;
//初始化数据库 连接数据库 设置字符集 
//host MYSQL数据库ip port数据库端口 Db数据库名称 usr数据库用户 pwd数据库的用户密码
//charset字符集 Msg 返回的消息
// int返回结果  0表示成功 1表示失败
	//&conn,"localhost","root","12345678","hxxword",0,NULL,CLIENT_FOUND_ROWS
	int ConnMySQL(const char *host,const char *port,const char *Db,const char *usr,const char *pwd,const char *charset,string& Msg);
//////////////////////////////////////////////////////////////////////
//查询功能 SQL 查询的SQL语句 Cnum 查询的烈属
//
	string SelectData(char * SQL,int Cnum,string& Msg);

///////////7.31@hxx////////////
//插入功能 
//SQL 查询的SQL语句 Msg是返回的报告信息 0 successful 1 failture
	int InsertData(char *SQL,string& Msg);
	int UpdateData(char *SQL,string& Msg);
//删除功能
//SQL查询的SQL语句 Msg报告信息  0successful 1 failture
	int DeleteData(char *SQL,string& Msg);
	void CloseMySQLConn();//关闭sql连接
	int createTable(char* SQL,string& Msg);
};
#endif
