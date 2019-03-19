#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<iostream>

#include "glog/logging.h"   // glog 头文件

using namespace std;


// #define GOOGLE_GLOG_DLL_DECL

char *getUrlParam(const char *sUrl,const char *sParam) {
	if(sUrl == NULL || sParam == NULL){
		return NULL;
	}
	char *tmp_url = new char[strlen(sUrl)+1];
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
	if(strcmp(key,sParam)==0){
		delete[] tmp_url;
		tmp_url=nullptr;
		return value;
	}
	
	while(param != NULL) {
		param = strtok_r(NULL,delims,&tokptr_url);
		key = strtok_r(param,equal_sign,&tokptr_param);
		value = strtok_r(NULL,equal_sign,&tokptr_param);
		cout<<"2param: "<<param<<"    "<<"key: "<<key<<"    "<<"value: "<<value<<endl;
		if(strcmp(key,sParam)==0){
			delete[] tmp_url;
			tmp_url=nullptr;
			return value;
		}
	}   
	delete[] tmp_url;
	tmp_url=nullptr;
	return nullptr;
}

int main(int argc,char** argv) {
	google::InitGoogleLogging(argv[0]);    // 初始化
	FLAGS_log_dir="/var/log/fmms";
	printf("Content-type:text/text\n\n"); //把后面要打印的信息输出到页面
	printf("Hello,World!!!");
	cout<<"log_path: "<<argv[0]<<endl;

	LOG(INFO) << "init glog "<<argc; 
	LOG(INFO) << "glog test 1!!!";
	LOG(INFO) << "glog test 2!!!";
	LOG(INFO) << "glog test 2!!!";
	LOG(INFO) << "glog test 3!!!";
	LOG(INFO) << "glog test qewrwerwtrtrtretert!!!";

	char* queryParam = getenv("QUERY_STRING"); 
	cout<<"QUERY_STRING: "<<queryParam<<endl;
	cout<<"a:"<<getUrlParam(queryParam,"a")<<endl;
	cout<<"b:"<<getUrlParam(queryParam,"b")<<endl;
	cout<<"c:"<<getUrlParam(queryParam,"c")<<endl;
	LOG(INFO) << getUrlParam(queryParam,"a");
}
