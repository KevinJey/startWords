函数分析:
	string VspdToMySQL::SelectData(char *SQL,int Cnum,char *Msg);
很多函数的写法都很类似 把一个结果的指针或者引用作为参数传递进去 返回值仅仅表示一个状态 错误状态的信息被写在形式参数之内。


	MYSQL_ROW m_row;
	MYSQL_RES *m_res;

	char sql[2048];
	sprintf(sql,SQL);
	int rnum = 0;
	char rg = 0x06; //行分割
	char cg = {0x05};
if(mysql_query(&mysql,sql)){ 
//执行这个查询函数 并得出结果 存放在mysql中 mysql是一个字符串 存放了函数运行的结果 也就是mysql数据库运行的结果
	Msg = "select ps_info Error";
		return "";
	}
	m_res = mysql_store_result(&mysql);
读出这个运行结果 放到内置的类型当中
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
读出数据把它存放在str中 然后返回str字符串 表示查询的结果