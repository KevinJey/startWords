#include "VspdToMySQL.h"
#include "mysql.h"
VspdToMySQL::VspdToMySQL(){

}
VspdToMySQL::~VspdToMySQL(){

}

//主机 端口 数据库 用户名密码 字符类型 报告信息
int VspdToMySQL::ConnMySQL(const char *host,const char* port,const char *Db,
	const char *usr,const char *pwd,const char *charset,string& Msg){
	cout<<"YES"<<endl;
	//连接数据库可以分为三个步骤 初始化数据库 连接数据库 设置字符类型
	if(mysql_init(&mysql)==NULL){
		Msg = "inital mysql handle error";
		return 1;
	}

	if(mysql_real_connect(&mysql,host,usr,pwd,Db,0,NULL,0)==NULL){
		Msg = "Fail to connect databases:Error!";
		return 1;
	}

	if(mysql_set_character_set(&mysql,charset)!=0){
		Msg = "mysql_set_character_set error";
		return 1;
	}
	return 0;
}

int VspdToMySQL::createTable(char *SQL,string &Msg){
	//char sql[100];
	//sprintf(sql,"%s",SQL);
	if(mysql_query(&mysql,SQL)){
		Msg = "createTable error";
		return 1;
	}
	return 0;
}
//查询数据
string VspdToMySQL::SelectData(char * SQL,int Cnum,string& Msg){
	MYSQL_ROW m_row;
	MYSQL_RES *m_res;

	char sql[2048];
	sprintf(sql,"%s",SQL);
	int rnum = 0;
	char rg = 0x06; //行分割
	char cg = {0x05}; //字段分开

	if(mysql_query(&mysql,sql)){
		Msg = "select ps_info Error";
		return "";
	}
	m_res = mysql_store_result(&mysql);

	if(m_res ==NULL){
		Msg = "select username Error";
		return "";
	}
	string str = "";
	while(m_row = mysql_fetch_row(m_res)){
		for(int i = 0;i < Cnum;++i){
			str += m_row[i];
			str += rg;

		}
		str += rg;
		rnum ++;
	}
	mysql_free_result(m_res);

	return str;
}

int VspdToMySQL::InsertData(char *SQL,string& Msg){
	//char sql[2048];
	//sprintf(sql,"%s",SQL);
	if(mysql_query(&mysql,SQL)){//成员变量mysql相当于一个句柄
		Msg = "InsertData error";
		return 1;
	}
	return 0;
}

int VspdToMySQL::UpdateData(char *SQL,string& Msg){
	char sql[2048];
	sprintf(sql,"%s",SQL);
	if(mysql_query(&mysql,sql)){
		Msg = "Update Data error";
		return 1;
	}
	return 0;
}

int VspdToMySQL::DeleteData(char *SQL,string& Msg){
	char sql[2048];
	sprintf(sql,"%s",SQL);

	if(mysql_query(&mysql,sql)){
		Msg = "Delete Data error";
		return 1;
	}
	return 0;
}

void VspdToMySQL::CloseMySQLConn(){
	cout << "Database has been closed!" << endl;
	mysql_close(&mysql);
}
