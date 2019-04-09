#include "../include/Handler.h"
#include "../include/DAO.h"
#include "../include/util.h"

#include <glog/logging.h>
#include <time.h>


using namespace std;
using namespace wyx;


MemberDAO memberDAO;
ManagerDAO managerDAO;

unordered_map<string,unordered_map<string,function<void ()>>>* wyx::Handler::webResource = new unordered_map<string,unordered_map<string,function<void ()>>>();

void wyx::Handler::response(Json::Value &JsonRoot,const bool &status){
	Json::Value JsonResult;
	JsonResult["status"] = Json::Value(status);
	JsonResult["data"] = JsonRoot;
	LOG(INFO)<<"response json: "<<endl<<JsonResult.toStyledString();
	printf("Content-type:application/json; charset=utf-8\n\n");
	cout<<JsonResult.toStyledString()<<endl;
}

void wyx::Handler::response(const bool &status){
	Json::Value JsonResult;
	JsonResult["status"] = Json::Value(status);
	LOG(INFO)<<"response status: "<<endl<<JsonResult.toStyledString();
	printf("Content-type:application/json; charset=utf-8\n\n");
	cout<<JsonResult.toStyledString()<<endl;
}

void wyx::Handler::response(const string &text){
	LOG(INFO)<<"response text: "<<endl<<text;
	printf("Content-type:text/plain; charset=utf-8\n\n");
	cout<<text<<endl;
}

void wyx::Handler::redirect(const string &url){
	LOG(INFO)<<"redirect to "<<url;
	printf("Status: 302 Found");
	cout << "HTTP/1.1 302 Moved Permanently\n";
	cout << "Location: "<<url<<"\n"<<endl;
}



unordered_map<string,unordered_map<string,function<void ()>>>* wyx::Handler::getWebResource(){

	(*webResource)["^/something/?$"]["POST"]=[](){

	};

	(*webResource)["^/member_register/?$"]["POST"]=[](){
		LOG(INFO)<<"memeber_register[POST]";

		RequestParam requestParam;

		shared_ptr<Member> member = make_shared<Member>();
		member->account=requestParam.getRequestValue("account");
		member->password=requestParam.getRequestValue("password");
		member->name=requestParam.getRequestValue("name");
		member->sex=requestParam.getRequestValue("sex");
		//获取系统当前时间戳
		time_t now_time = time(nullptr);
		member->start_date=now_time;
		member->end_date=-1;
		memberDAO.add(member.get());
		response(true);
	};

	(*webResource)["^/member_update/?$"]["POST"]=[](){
		LOG(INFO)<<"memeber_update[POST]";

		RequestParam requestParam;

		shared_ptr<Member> member = make_shared<Member>();

		member->id=stoi(requestParam.getRequestValue("id"));
		member->account=requestParam.getRequestValue("account");
		member->password=requestParam.getRequestValue("password");
		member->name=requestParam.getRequestValue("name");
		member->sex=requestParam.getRequestValue("sex");
		member->start_date=stoi(requestParam.getRequestValue("start_date"));
		member->end_date=stoi(requestParam.getRequestValue("end_date"));

		memberDAO.update(member.get());

		response(true);
	};

	(*webResource)["^/member_register_check_account/?$"]["GET"]=[](){
		LOG(INFO)<<"member_register_check_account";

		RequestParam requestParam;
		string account = requestParam.getRequestValue("account");
		shared_ptr<Member> member(memberDAO.get(account));
		response(member?false:true);
	};

	(*webResource)["^/member_login/?$"]["POST"]=[](){
		LOG(INFO)<<"member_login";

		RequestParam requestParam;
		string account = requestParam.getRequestValue("account");
		string password = requestParam.getRequestValue("password");

		shared_ptr<Member> member(memberDAO.get(account,password));
		if(member){
			Json::Value JsonRoot;
			JsonRoot["id"] = Json::Value(member->id);
			JsonRoot["name"] = Json::Value(member->name);
			JsonRoot["account"] = Json::Value(member->account);
			JsonRoot["password"] = Json::Value(member->password);
			JsonRoot["sex"] = Json::Value(member->sex);
			JsonRoot["start_date"] = Json::Value(member->start_date);
			JsonRoot["end_date"] = Json::Value(member->end_date);

			response(JsonRoot);
		}else{
			response(false);
		}
	};

	(*webResource)["^/member_list/?$"]["GET"]=[](){
		LOG(INFO)<<"member_list";

		shared_ptr<vector<shared_ptr<Member>>> memberList(memberDAO.list());
		Json::Value JsonRoot;
		for(auto &member : *memberList){
			Json::Value JsonMember;
			JsonMember["id"] = Json::Value(member->id);
			JsonMember["name"] = Json::Value(member->name);
			JsonMember["account"] = Json::Value(member->account);
			JsonMember["password"] = Json::Value(member->password);
			JsonMember["sex"] = Json::Value(member->sex);
			JsonMember["start_date"] = Json::Value(member->start_date);
			JsonMember["end_date"] = Json::Value(member->end_date);

			JsonRoot["memberList"].append(JsonMember);
		}

		response(JsonRoot);
	};

	(*webResource)["^/manager_login/?$"]["POST"]=[](){
		LOG(INFO)<<"manager_login";

		RequestParam requestParam;
		string account = requestParam.getRequestValue("account");
		string password = requestParam.getRequestValue("password");

		shared_ptr<Manager> manager(managerDAO.get(account,password));
		if(manager){
			Json::Value JsonRoot;
			JsonRoot["id"] = Json::Value(manager->id);
			JsonRoot["account"] = Json::Value(manager->account);

			response(JsonRoot);
		}else{
			response(false);
		}
	};

	(*webResource)["^/test/?$"]["GET"]=[](){
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

		response(JsonRoot);
	};	


	return webResource;
}

