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
using namespace sql;




#define DBHOST "tcp://localhost:3306"  
#define USER "root"  
#define PASSWORD "root"  


char *getUrlParam(const char *sUrl,const char *sParam) {
	LOG(INFO)<<"sUrl:"<<sUrl<<"    "<<"sParam:"<<sParam;
	if(sUrl == NULL || sParam == NULL){
		return NULL;
	}
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

	cout<<"1param: "<<param<<"    "<<"key: "<<key<<"    "<<"value: "<<value<<endl;
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
		cout<<"2param: "<<param<<"    "<<"key: "<<key<<"    "<<"value: "<<value<<endl;
		if(func_match_handler()){
			return value;
		}
	}   
	LOG(INFO)<<"没找到 sParam:"<<sParam;
	delete[] tmp_url;
	tmp_url=nullptr;
	return nullptr;
}

void sql_test(){
	Driver *driver;  
	Connection *conn;  
	driver = get_driver_instance();  
	conn = driver->connect(DBHOST, USER, PASSWORD);  
	/*
	   默认的话为自动提交， 
	   每执行一个update ,delete或者insert的时候都会自动提交到数据库，无法回滚事务。 
	   设置connection.setautocommit(false);只有程序调用connection.commit()的时候才会将先前执行的语句一起提交到数据库，这样就实现了数据库的事务。

	   true：sql命令的提交（commit）由驱动程序负责 
	   false：sql命令的提交由应用程序负责，程序必须调用commit或者rollback方法

	   */
	conn->setAutoCommit(0);  
	cout<<"DataBase connection autocommit mode = "<<conn->getAutoCommit()<<endl;  
	delete conn;  
	driver = NULL;  
	conn = NULL;  
}

int main(int argc,char** argv) {
	// 初始化GLOG
	google::InitGoogleLogging(argv[0]); 
	// 设置日志目录
	FLAGS_log_dir="/var/log/fmms";
	// 缓存小于或等于这个级别的日志信息. (-1表示不缓存; 0表示只缓存INFO级别日志; ...) 
	FLAGS_logbuflevel = -1;

	printf("Content-type:text/text\n\n"); //把后面要打印的信息输出到页面
	printf("Hello,World!!!");
	cout<<"log_path: "<<argv[0]<<endl;

	LOG(INFO) << "init glog "; 
	LOG(INFO) << "glog test 1!!!";
	LOG(INFO) << "glog test 2!!!";
	LOG(INFO) << "glog test 2!!!";
	LOG(INFO) << "glog test 3!!!";
	LOG(INFO) << "glog test qewrwerwtrtrtretert!!!";
	LOG(INFO) << argc;

	char* queryParam = getenv("QUERY_STRING"); 
	cout<<"QUERY_STRING: "<<queryParam<<endl;
	cout<<"a:"<<getUrlParam(queryParam,"a")<<endl;
	cout<<"b:"<<getUrlParam(queryParam,"b")<<endl;
	cout<<"c:"<<getUrlParam(queryParam,"c")<<endl;
	cout<<"e:"<<getUrlParam(queryParam,"e")<<endl;

	sql_test();
}
