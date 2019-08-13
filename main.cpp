/***************************************************

	*Modify@hxx 2019.7.31*
	新增加了VspdToMysql类 用来封装MySQL的操作
	


**************************************************/


#include <mysql.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "VspdToMySQL.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////
class vocabulary
{
public:
	enum TYPE
	{
		n,
		v,
		adj,
		adv
	};
	string m_word;
	string m_translation;
	int level;
	vocabulary(string word = "", string translation = "")
	:m_word(word), m_translation(translation),level(1){}
	ostream& operator<<(ofstream& out);


};
ostream& vocabulary::operator<<(ofstream& out){
	//ostream& out;
	out << m_word<<" "  << " " <<  m_translation << endl;
	return out;
}
class mainWindow
{
public:
	VspdToMySQL *mysql_conn;
	vector<vocabulary> dictionary;
	mainWindow();
	~mainWindow();
	void welcome(){
		cout<<"\033[1m\033[3m\033[31m   Weoclme to 星羊单词"<<endl;
		int randnum = rand()%size;
		cout<<"\033[34m\033[3m\033[1m"<<"*"<<encouage[randnum]<<"*\033[0m"<<endl;

		cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
		cout<<"[1] CET4"<<endl
			<<"[2] CET6"<<endl
			<<"[3] 考研单词"<<endl;
	}
	void choose(){
		cout<<"选择一本词典:";
		string choosen;
		cin>>choosen;
		read(choosen);
	}
	void read(string choosen);	
	void recite();
private:
	string encouage[100]={
		"Do one thing at a time, and do well.",
		"Keep on going never give up.",
		"Whatever is worth doing is worth doing well.",
		"Believe in yourself.",
		"I can because i think i can.",
		"Action speak louder than words.",
		"The best preparation for tomorrow is doing your best today."
	};
	int size = 6;
};
mainWindow::mainWindow(){
	mysql_conn = new VspdToMySQL();
}
mainWindow::~mainWindow(){
	delete mysql_conn;
}

void mainWindow::read(string choosen){
		//从被选择的文件中读入单词
		int num = 0;
		int k = 0;
		while(choosen[k]){
			num = num*10 + choosen[k]-'0';
			k++;
		}
		string bookName;
		switch(num){
			case 1:bookName = "CET4";break;
			case 2:bookName = "CET6";break;
			case 3:bookName = "Kaoyan";break;
			default:{
				cout<<"Error!"<<endl;
				exit(0);
			}
		}
		bookName += ".txt";
		ifstream in(bookName);
		string outfilename = "local" + bookName;
		ofstream out(outfilename);
		cout<<"Connecting..."<<endl;

		VspdToMySQL mysql_conn ;
		//package
		string host = "localhost";
		string port = "3306";
		string db = "hxxword";
		string usr = "root";
		string pwd = "12345678";
		string charset = "utf8";
		string Msg;
		//int ConnMySQL(char *host,char *port,char *Db,char *usr,char *pwd,char *charset,string Msg);
		if(mysql_conn.ConnMySQL(host.data(),port.data(),db.data(),usr.data(),pwd.data(),charset.data(),Msg)){
			cout<<"Attemp connect to database error!"<<endl;
			cout<<"212"<<endl;
			cout<<Msg<<endl;
			return ;
		}
		cout<<"Connecting!"<<endl;
		if(mysql_conn.createTable("create table word(name varchar(100) character set utf8 collate utf8_unicode_ci"
			",speaking varchar(100) character set utf8 collate utf8_unicode_ci,"
			"translation varchar(100) character set utf8 collate utf8_unicode_ci);",Msg)){
			cout << Msg <<endl;
		//	return ;
		}
		while(in.good()){
			string word,speaking,translation;
			in>>word>>speaking;
			//cout << word << " " << speaking << " ";
			getline(in,translation);
			//cout << translation << endl;
			string str = "insert into word values(";
			mysql_query(&mysql_conn.mysql,(str +"'"+word+"'" + ","+ "'" + speaking + "'" + "," +"'"  + translation + + "'" + ");").data() );
			/*sprintf(temp_str,"insert into word values(%s,%s,%s)",word,speaking,translation);
			cout << temp_str <<endl;
			string Msg;
			if(mysql_conn.InsertData(temp_str,Msg)){
				cout << Msg <<endl;
			//	return ;
			}*/
		}

		mysql_conn.CloseMySQLConn();

	}


int main(int argc, char const *argv[])
{
	mainWindow m1;

	while(1){
		m1.welcome();
		m1.choose();
	}
	return 0;
}
