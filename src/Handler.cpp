#include "../include/Handler.h"

#include <glog/logging.h>

using namespace std;

unordered_map<string,unordered_map<string,function<void ()>>>* wyx::Handler::webResource = new unordered_map<string,unordered_map<string,function<void ()>>>();

void wyx::Handler::response(Json::Value &JsonRoot){
	LOG(INFO)<<"response json: "<<endl<<JsonRoot.toStyledString();
	printf("Content-type:application/json; charset=utf-8\n\n");
	cout<<JsonRoot.toStyledString()<<endl;
}

void wyx::Handler::redirect(string &url){
	LOG(INFO)<<"redirect to "<<url;
	printf("Status: 302 Found");
	cout << "HTTP/1.1 302 Moved Permanently\n";
	cout << "Location: "<<url<<"\n"<<endl;
}

unordered_map<string,unordered_map<string,function<void ()>>>* wyx::Handler::getWebResource(){
	(*webResource)["^/test/?$"]["GET"]=[](){
		//printf("Content-type:text/html; charset=utf-8\n\n"); //把后面要打印的信息输出到页面
		//printf("Content-type:application/json; charset=utf-8\n\n"); //把后面要打印的信息输出到页面


		Json::Value JsonRoot;
		JsonRoot["age"] = Json::Value(22);
		// 写入浮点型数字
		JsonRoot["height"] = Json::Value(1.78);
		// 写入布尔型
		JsonRoot["play_football"] = Json::Value(true);
		// 写入Json对象
		Json::Value JsonObj;
		JsonObj["sometime"] = Json::Value(2018);
		JsonObj["someone"] = Json::Value("Kelly");
		JsonObj["somewhere"] = Json::Value("city");
		JsonRoot["object"] = JsonObj;

		// 单个键写入数字数组
		JsonRoot["number_array"].append(1);
		JsonRoot["number_array"].append(2);
		JsonRoot["number_array"].append(3);
		JsonRoot["number_array"].append(4);
		// 单个键写入字符串数组
		JsonRoot["string_array"].append("string01");
		JsonRoot["string_array"].append("string02");
		JsonRoot["string_array"].append("string03");
		// 写入Json对象数组，即数组由对象构成
		Json::Value JsonArr1, JsonArr2, JsonArr3;
		JsonArr1["string1"] = Json::Value("1-1");
		JsonArr1["string2"] = Json::Value("1-2");
		JsonArr2["string1"] = Json::Value("2-1");
		JsonArr2["string2"] = Json::Value("2-2");
		JsonArr3["string1"] = Json::Value("3-1");
		JsonArr3["string2"] = Json::Value("3-2");
		JsonRoot["object_array"].append(JsonArr1);
		JsonRoot["object_array"].append(JsonArr2);
		JsonRoot["object_array"].append(JsonArr3);

		//cout<<JsonRoot.toStyledString()<<endl;
		response(JsonRoot);


	};	
	return webResource;
}

