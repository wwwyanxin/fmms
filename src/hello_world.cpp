#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<iostream>

// glog 头文件
#include "glog/logging.h"   

// MySQL  Connector/C++
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/metadata.h>
#include <cppconn/exception.h>


using namespace std;
//using namespace sql;




#define DBHOST "tcp://localhost:3306"  
#define USER "root"  
#define PASSWORD "123"  
#define DATA_BASE "fmms"


string getUrlParam(const char *sUrl,const char *sParam) {
	if(sUrl == NULL || sParam == NULL || strcmp(sUrl,"")==0 || strcmp(sParam,"")==0 ){
		LOG(INFO)<<"参数为空";
		return "";
	}
	LOG(INFO)<<"sUrl:"<<sUrl<<"    "<<"sParam:"<<sParam;
	char *tmp_url = new char[strlen(sUrl)+1]();
	strcpy(tmp_url,sUrl);
	cout<<"sUrl: "<<sUrl<<"    "<<"sParam: "<<sParam<<endl;
	const char *delims = "&";
	const char *equal_sign = "=";
	char *param = NULL;
	char *key = NULL;
	char *value = NULL;

	char *tokptr_url = nullptr;	
	char *tokptr_param = nullptr;

	param = strtok_r(tmp_url,delims,&tokptr_url);
	key = strtok_r(param,equal_sign,&tokptr_param);
	value = strtok_r(NULL,equal_sign,&tokptr_param);

	auto func_match_handler = [&](){
		if(strcmp(key,sParam)!=0){
			return false;
		}
		delete[] tmp_url;
		tmp_url=nullptr;
		return true;
	};
	if(func_match_handler()){
		return value;
	}

	while((param = strtok_r(NULL,delims,&tokptr_url))&& param != NULL) {
		key = strtok_r(param,equal_sign,&tokptr_param);
		value = strtok_r(NULL,equal_sign,&tokptr_param);
		if(func_match_handler()){
			return value != NULL ? value : "";
		}
	}   
	LOG(INFO)<<"没找到 sParam:"<<sParam;
	delete[] tmp_url;
	tmp_url=nullptr;
	return "";
}

void sql_test(){
	string sql_str="select * from member where name = ? ";
	sql::Driver *driver;  
	sql::Connection *conn;  
	sql::PreparedStatement *pstmt;
	sql::ResultSet *res;

	try{
		driver = get_driver_instance();  
		conn = driver->connect(DBHOST, USER, PASSWORD);  
		conn->setSchema(DATA_BASE);
		pstmt = conn->prepareStatement(sql_str);

		pstmt->setString(1,"阿水淀粉");

		res = pstmt->executeQuery();

		LOG(INFO)<<"sqlQuery!!";

		while (res->next()){
			LOG(INFO)<<"res->next();";
			string str_res = res->getString("name");
			cout << "QueryRes: " <<str_res<<endl;
			cout<<endl;
		}

		delete res;
		delete pstmt;
		delete conn;  

	} catch (sql::SQLException& e) {
		LOG(ERROR) << "# ERR: SQLException in " << __FILE__;
		LOG(ERROR) << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		LOG(ERROR) << "# ERR: " << e.what();
		LOG(ERROR) << " (MySQL error code: " << e.getErrorCode();
		LOG(ERROR) << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
	res = nullptr;
	pstmt = nullptr;
	driver = nullptr;  
	conn = nullptr;  
	return;
}

int main(int argc,char** argv) {
	// 初始化GLOG
	google::InitGoogleLogging(argv[0]); 
	// 设置日志目录
	FLAGS_log_dir="/var/log/fmms";
	// 缓存小于或等于这个级别的日志信息. (-1表示不缓存; 0表示只缓存INFO级别日志; ...) 
	FLAGS_logbuflevel = -1;

	LOG(INFO)<<"argc:"<<argc;


	printf("Content-type:text/html; charset=utf-8\n\n"); //把后面要打印的信息输出到页面
	printf("Hello,World!!!<br>");
	cout<<"log_path: "<<argv[0]<<endl;

	LOG(INFO) << "init glog "; 

	char* queryParam = getenv("QUERY_STRING"); 
	cout<<"QUERY_STRING: <br>"<<queryParam<<endl;

	cout<<"a:"<<getUrlParam(queryParam,"a")<<"<br>"<<endl;
	cout<<"b:"<<getUrlParam(queryParam,"b")<<"<br>"<<endl;
	cout<<"c:"<<getUrlParam(queryParam,"c")<<"<br>"<<endl;
	cout<<"e:"<<getUrlParam(queryParam,"e")<<"<br>"<<endl;
	
	sql_test();
}
