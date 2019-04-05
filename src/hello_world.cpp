#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<iostream>
#include<unordered_map>
#include<memory>

// glog 头文件
#include <glog/logging.h>  

// MySQL  Connector/C++
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/metadata.h>
#include <cppconn/exception.h>
#include <json/json.h>

// Redis
#include <hiredis/hiredis.h>

#include "../include/util.h"
#include "../include/WebServer.h"



using namespace std;




#define DBHOST "tcp://localhost:3306"  
#define USER "root"  
#define PASSWORD "123"  
#define DATA_BASE "fmms"


/*
vector<string>* string_split(const string& str, const string& delims){
	string::size_type pos1,pos2;
	pos2 = str.find(delims);
	pos1 = 0;

	vector<string>* result = new vector<string>();
	while(string::npos != pos2){
		result->push_back(str.substr(pos1,pos2-pos1));

		pos1 = pos2 + delims.length();
		pos2 = str.find(delims,pos1);
	}
	if(pos1 != str.length()){
		result->push_back(str.substr(pos1));
	}

	return result;
}

unordered_multimap<string,string>* getParamMultimap(const string &str,const string &delims){
	unordered_multimap<string,string> *result = new unordered_multimap<string,string>();
	shared_ptr<vector<string>> segment_list (string_split(str,delims));
	for(string &item : *segment_list){
		string::size_type equal_sign_pos = item.find("=");
		// 如果等号在开头，或者没有等号，那么此段参数格式错误，跳过
		if(equal_sign_pos == 0 || equal_sign_pos == string::npos){
			LOG(WARNING)<<"getParamMultimap WARNING : 等号格式错误";
			continue;
		}
		shared_ptr<vector<string>> param (string_split(item,"="));
		if(param->size()==0 || param->size()>2){
			LOG(WARNING)<<"getParamMultimap WARNING : 参数数量错误";
			continue;
		}else if(param->size() == 1){
			LOG(INFO)<<"getParamMultimap INFO : 空值";
			result->insert(pair<string,string>(param->at(0),""));
		}else{
			result->insert(pair<string,string>(param->at(0),param->at(1)));
		}
	}
	return result;
}

string* getParamValue(const string &str,const string &key,const string &delims){
	shared_ptr<unordered_multimap<string,string>> paramMultimap (getParamMultimap(str,delims));
	unordered_multimap<string,string>::const_iterator pairs = paramMultimap->find(key);

	if(pairs == paramMultimap->end()){
		LOG(INFO)<<"未找到 param value of key:"<<key;
		return nullptr;
	}else{
		LOG(INFO)<<"找到param:  "<<key<<"="<<pairs->second;
		string *result =  new string(pairs->second);
		LOG(INFO)<<"getParamValue *result="<<*result;
		return result;
	}
}

vector<string>* getParamValueList(const string &str,const string &key,const string &delims){
	shared_ptr<unordered_multimap<string,string>> paramMultimap (getParamMultimap(str,delims));
	pair<unordered_map<string,string>::const_iterator, unordered_map<string,string>::const_iterator> range = paramMultimap->equal_range(key);

	if(range.first == range.second){
		LOG(INFO)<<"未找到 param value of key:"<<key;
		return nullptr;
	}else{
		vector<string>* result = new vector<string>();
		for(auto iter=range.first;iter!=range.second;++iter){
			LOG(INFO)<<"找到param:  "<<key<<"="<<iter->second;
			result->insert(result->begin(),iter->second);
		}
		return result;
	}
}

string* getUrlValue(const string &key){
	return getParamValue(getenv("QUERY_STRING"),key,"&");
}

vector<string>* getUrlValueList(const string &key){
	return getParamValueList(getenv("QUERY_STRING"),key,"&");
}
  */ 

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

int json_test(){
	string json_str ="{\"id\":1,\"name\":\"偶人民防空\"}";
	Json::Reader reader;
	Json::Value json_root;
	if(reader.parse(json_str,json_root))
	{
		if(!json_root["id"].isNull())
		{
			cout << json_root["id"].asInt() << endl;
			cout << json_root["name"].asString()<< endl;

		}

		cout<<json_root.toStyledString()<<endl;


	}


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

	cout<<JsonRoot.toStyledString()<<endl;


	return 0;
}

void redirect_test(const string &url){
	printf("Status: 302 Found");
	cout << "HTTP/1.1 302 Moved Permanently\n";
	 
	cout << "Location: "<<url<<"\n"<<endl;
}


void redis_test(){

	struct timeval timeout = {2, 0};    //2s的超时时间

	redisContext *pRedisContext = (redisContext*)redisConnectWithTimeout("127.0.0.1", 6379, timeout);    //redisContext是Redis操作对象
	if ( (NULL == pRedisContext) || (pRedisContext->err) )
	{
		if (pRedisContext)
		{
			LOG(ERROR)<<"connect error: "<< pRedisContext->errstr;
			cout << "connect error:" << pRedisContext->errstr << endl;
		}
		else
		{
			LOG(ERROR)<<"connect error: can't allocate redis context.";
			cout << "connect error: can't allocate redis context." << std::endl;
		}
		return ;
	}

	redisCommand(pRedisContext,"SET %s %s","keyabc","value-但是放水淀粉"); 

	redisReply *pRedisReply = (redisReply*)redisCommand(pRedisContext,"GET %s","keyabc");
	if(pRedisReply->str == nullptr)
	{
		LOG(ERROR)<<pRedisContext->errstr;
		return;
	}
	cout<<"keyabc是："<<pRedisReply->str<<endl;
	freeReplyObject(pRedisReply);




	redisCommand(pRedisContext,"HMSET fmms_user:123 name wyx birthday 1996");
	
	redisCommand(pRedisContext,"EXPIRE fmms_user:123 60");

	
	pRedisReply = (redisReply*)redisCommand(pRedisContext,"TTL fmms_user:123");
	if(pRedisReply->str == nullptr)
	{
		LOG(INFO)<<"reply type:"<<pRedisReply->type<<endl<<"REDIS_REPLY_STATUS="<<REDIS_REPLY_STATUS<<"  REDIS_REPLY_ERROR="<<REDIS_REPLY_ERROR<<"  REDIS_REPLY_INTEGER="<<REDIS_REPLY_INTEGER<<"    REDIS_REPLY_NIL="<<REDIS_REPLY_NIL<<"   REDIS_REPLY_STRING="<<REDIS_REPLY_STRING<<"   REDIS_REPLY_ARRAY="<<REDIS_REPLY_ARRAY;
	}
	LOG(INFO)<<"reply:"<<pRedisReply->integer;
	cout<<"TTL fmms_user:123 =  "<<pRedisReply->integer<<endl;
	freeReplyObject(pRedisReply);


	/*
	redisCommand(pRedisContext,"EXPIRE fmms_user:123 60");
	*/


	pRedisReply = (redisReply*)redisCommand(pRedisContext,"HGET fmms_user:123 name");
	/*
	pRedisReply = (redisReply*)redisCommand(pRedisContext,"HGETALL fmms_user:123");
	for(size_t i=0;i<pRedisReply->elements;++i)
	{
		cout<<"fmms_user:123   "<<pRedisReply->element[i]->str<<endl;
	}
	*/
	cout<<"fmms_user:123 name="<<pRedisReply->str<<endl;
	freeReplyObject(pRedisReply);




	// 释放redisConnect()所产生的连接
	redisFree(pRedisContext);

}

void cookie_test(){
	char* cookie_tmp = getenv("HTTP_COOKIE");
	if(cookie_tmp!=nullptr)
	{
		LOG(INFO)<<"cookie:"<<cookie_tmp<<endl;
	}
	printf("Set-Cookie: manager_id=%d;Max-Age=%ld;Path=/; HttpOnly\n",123456,static_cast<long>(600));
	printf("Set-Cookie: name=%d;Max-Age=%ld;\n",3123424,static_cast<long>(600));
	printf("Set-Cookie: test=%d;Max-Age=%ld;\n",9847239,static_cast<long>(600));


}


int main(int argc,char** argv) {
	// 初始化GLOG
	google::InitGoogleLogging(argv[0]); 
	// 设置日志目录
	FLAGS_log_dir="/var/log/home";
	// 缓存小于或等于这个级别的日志信息. (-1表示不缓存; 0表示只缓存INFO级别日志; ...) 
	FLAGS_logbuflevel = -1;

	LOG(INFO)<<"argc:"<<argc;

	//regex reg1("test");
	//regex reg1("^test$");
	//smatch sm_result;
	//string testStr = "test";

	//LOG(INFO)<<"regex test = "<<regex_match(testStr,sm_result,reg1);

	wyx::WebServer webServer;
	webServer.init();
	webServer.start();

	//redirect_test("http://www.baidu.com");

	//	cookie_test();

	/*
	printf("Content-type:text/html; charset=utf-8\n\n"); //把后面要打印的信息输出到页面
	printf("Hello,World!!!<br>");
	cout<<"log_path: "<<argv[0]<<endl;

	LOG(INFO) << "init glog "; 

	const char* queryParam = getenv("QUERY_STRING"); 
	cout<<"QUERY_STRING: "<<queryParam<<"<br>";
	cout<<"PATH_INFO: "<<getenv("PATH_INFO")<<"<br>";
	cout<<"REQUEST_METHOD: "<<getenv("REQUEST_METHOD")<<"<br>";
	//cout<<"CONTENT_LENGTH: "<<(int)*getenv("CONTENT_LENGTH")<<"<br>";
	//cout<<"CONTENT_TYPE: "<<getenv("CONTENT_TYPE")<<"<br>";
	cout<<"SCRIPT_FILENAME: "<<getenv("SCRIPT_FILENAME")<<"<br>";
	cout<<"SCRIPT_NAME: "<<getenv("SCRIPT_NAME")<<"<br>";
	*/

	/*
	cout<<"a:"<<getUrlParam(queryParam,"a")<<"<br>"<<endl;
	cout<<"b:"<<getUrlParam(queryParam,"b")<<"<br>"<<endl;
	cout<<"c:"<<getUrlParam(queryParam,"c")<<"<br>"<<endl;
	cout<<"e:"<<getUrlParam(queryParam,"e")<<"<br>"<<endl;
	*/

	/*shared_ptr<string> param_a (wyx::getUrlValue("a"));
	if(param_a!= nullptr){
		cout<<"a:"<<*param_a<<"<br>"<<endl;
	}else{
		cout<<"a:nullptr"<<"<br>"<<endl;
	}

	shared_ptr<string> param_b (wyx::getUrlValue("b"));
	if(param_b!= nullptr){
		cout<<"b:"<<*param_b<<"<br>"<<endl;
	}else{
		cout<<"b:nullptr"<<"<br>"<<endl;
	}

	shared_ptr<string> param_c (wyx::getUrlValue("c"));
	if(param_c!= nullptr){
		cout<<"c:"<<*param_c<<"<br>"<<endl;
	}else{
		cout<<"c:nullptr"<<"<br>"<<endl;
	}
	
	shared_ptr<string> param_e (wyx::getUrlValue("e"));
	if(param_e!= nullptr){
		cout<<"e:"<<*param_e<<"<br>"<<endl;
	}else{
		cout<<"e:nullptr"<<"<br>"<<endl;
	}

	shared_ptr<vector<string>> param_arr (wyx::getUrlValueList("arr"));
	if(param_arr!= nullptr){
		for(auto &item : *param_arr){
			cout<<"arr:"<<item<<"<br>"<<endl;
		}
	}else{
		cout<<"arr:nullptr"<<"<br>"<<endl;
	}

	//queryParam = "a=1&b=sdjskljfasfasd&l=sdfsd&c=123&d=sadfasfa&fsdf=dsf";
	shared_ptr<vector<string>> result(wyx::string_split(queryParam,"="));
	cout<<"size:"<<result->size()<<endl;
	sql_test();
	json_test();
	redis_test();
	*/
}
