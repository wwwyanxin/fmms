#include "../include/Handler.h"
#include "../include/DAO.h"
#include "../include/util.h"

#include <glog/logging.h>
#include <time.h>


using namespace std;
using namespace wyx;


MemberDAO memberDAO;
ManagerDAO managerDAO;
CoachDAO coachDAO;
VenueDAO venueDAO;
VenueTypeDAO venueTypeDAO;
CourseDAO courseDAO;


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

	(*webResource)["^/coach_list/?$"]["GET"]=[](){
		LOG(INFO)<<"coach_list";

		shared_ptr<vector<shared_ptr<Coach>>> coachList(coachDAO.list());
		Json::Value JsonRoot;
		for(auto &item : *coachList){
			Json::Value JsonList;
			JsonList["id"] = Json::Value(item->id);
			JsonList["name"] = Json::Value(item->name);
			JsonList["sex"] = Json::Value(item->sex);
			JsonList["entry_date"] = Json::Value(item->entry_date);
			JsonList["introduction"] = Json::Value(item->introduction);
			JsonList["status"] = Json::Value(item->status);

			JsonRoot["coachList"].append(JsonList);
		}

		response(JsonRoot);
	};

	(*webResource)["^/coach_add/?$"]["POST"]=[](){
		LOG(INFO)<<"coach_add[POST]";

		RequestParam requestParam;

		shared_ptr<Coach> coach = make_shared<Coach>();
		coach->name = requestParam.getRequestValue("name");
		coach->sex = requestParam.getRequestValue("sex");
		coach->entry_date = time(nullptr); //系统当前时间戳
		coach->introduction = requestParam.getRequestValue("introduction");
		coach->status = requestParam.getRequestValue("status");

		coachDAO.add(coach.get());
		response(true);
	};

	(*webResource)["^/coach_update/?$"]["POST"]=[](){
		LOG(INFO)<<"coach_update[POST]";

		RequestParam requestParam;

		shared_ptr<Coach> coach = make_shared<Coach>();
		coach->id = stoi(requestParam.getRequestValue("id"));
		coach->name = requestParam.getRequestValue("name");
		coach->sex = requestParam.getRequestValue("sex");
		coach->entry_date = stoi(requestParam.getRequestValue("entry_date"));
		coach->introduction = requestParam.getRequestValue("introduction");
		coach->status = requestParam.getRequestValue("status");

		coachDAO.update(coach.get());
		response(true);
	};

	(*webResource)["^/venue_list/?$"]["GET"]=[](){
		LOG(INFO)<<"venue_list";

		shared_ptr<vector<shared_ptr<Venue>>> venueList(venueDAO.list());
		Json::Value JsonRoot;
		for(auto &item : *venueList){
			Json::Value JsonList;
			JsonList["id"] = Json::Value(item->id);
			JsonList["name"] = Json::Value(item->name);
			JsonList["capacity"] = Json::Value(item->capacity);
			JsonList["status"] = Json::Value(item->status);

			Json::Value JsonType;
			JsonType["id"] = Json::Value(item->venue_type->id);
			JsonType["type"] = Json::Value(item->venue_type->type);
			
			JsonList["venue_type"] = JsonType;

			JsonRoot["venueList"].append(JsonList);
		}

		response(JsonRoot);
	};

	(*webResource)["^/venue_add/?$"]["POST"]=[](){
		LOG(INFO)<<"venue_add[POST]";

		RequestParam requestParam;

		shared_ptr<Venue> venue = make_shared<Venue>();
		venue->name = requestParam.getRequestValue("name");
		venue->capacity = stoi(requestParam.getRequestValue("capacity"));
		venue->status = requestParam.getRequestValue("status");
		venue->venue_type->id = stoi(requestParam.getRequestValue("venue_type[id]"));

		venueDAO.add(venue.get());
		response(true);
	};

	(*webResource)["^/venue_update/?$"]["POST"]=[](){
		LOG(INFO)<<"venue update[POST]";

		RequestParam requestParam;

		shared_ptr<Venue> venue = make_shared<Venue>();
		venue->id = stoi(requestParam.getRequestValue("id"));
		venue->name = requestParam.getRequestValue("name");
		venue->capacity = stoi(requestParam.getRequestValue("capacity"));
		venue->status = requestParam.getRequestValue("status");
		venue->venue_type->id = stoi(requestParam.getRequestValue("venue_type[id]"));

		venueDAO.update(venue.get());
		response(true);
	};

	(*webResource)["^/venue_type_list/?$"]["GET"]=[](){
		LOG(INFO)<<"venue_type_list[GET]";

		RequestParam requestParam;

		shared_ptr<vector<shared_ptr<VenueType>>> venueTypeList(venueTypeDAO.list());
		Json::Value JsonRoot;
		for(auto &item : *venueTypeList){
			Json::Value JsonList;
			JsonList["id"] = Json::Value(item->id);
			JsonList["type"] = Json::Value(item->type);

			JsonRoot["typeList"].append(JsonList);
		}

		response(JsonRoot);
	};

	(*webResource)["^/course_get_week"]["GET"]=[](){
		LOG(INFO)<<"course_get_week[GET]";

		RequestParam requestParam;
		int start_date = stoi(requestParam.getRequestValue("start_date"));

		shared_ptr<vector<shared_ptr<Course>>> courseList(courseDAO.getWeek(start_date));

		Json::Value JsonRoot;

		for(auto &item : *courseList){
			Json::Value JsonList;
			JsonList["id"] = Json::Value(item->id);
			JsonList["start_date"] = Json::Value(item->start_date);
			JsonList["start_hour"] = Json::Value(item->start_hour);
			JsonList["price"] = Json::Value(item->price);
			JsonList["capacity"] = Json::Value(item->capacity);
			JsonList["type"] = Json::Value(item->type);

			Json::Value JsonVenue;
			JsonVenue["id"] = Json::Value(item->venue->id);
			JsonVenue["name"] = Json::Value(item->venue->name);
			JsonVenue["capacity"] = Json::Value(item->venue->capacity);
			JsonVenue["status"] = Json::Value(item->venue->status);

			Json::Value JsonVenueType;
			JsonVenueType["id"] = Json::Value(item->venue->venue_type->id);
			JsonVenueType["type"] = Json::Value(item->venue->venue_type->type);

			Json::Value JsonCoach;
			JsonCoach["id"] = Json::Value(item->coach->id);
			JsonCoach["name"] = Json::Value(item->coach->name);
			JsonCoach["entry_date"] = Json::Value(item->coach->entry_date);
			JsonCoach["status"] = Json::Value(item->coach->status);
			JsonCoach["sex"] = Json::Value(item->coach->sex);
			JsonCoach["introduction"] = Json::Value(item->coach->introduction);

			JsonVenue["venue_type"] = JsonVenueType;
			JsonList["venue"] = JsonVenue;
			JsonList["coach"] = JsonCoach;

			JsonRoot["courseList"].append(JsonList);
		}

		response(JsonRoot);
	};

	(*webResource)["^/course_add_week/?$"]["POST"]=[](){
		LOG(INFO)<<"course_add_week[POST]";

		RequestParam requestParam;

		string json_str = requestParam.getRequestValue("courseList");
		Json::Reader reader;
		Json::Value JsonCourseList;

		auto courseList = make_shared<vector<shared_ptr<Course>>>();
		if(reader.parse(json_str,JsonCourseList))
		{
			int list_size = JsonCourseList.size();
			LOG(INFO)<<"list_size: "<<list_size;
			for(int i=0;i<list_size;i++){
				auto course = make_shared<Course>();

				course->id = JsonCourseList[i]["id"].asInt();
				course->start_hour = JsonCourseList[i]["start_hour"].asString();
				course->start_date = JsonCourseList[i]["start_date"].asInt();
				course->capacity = JsonCourseList[i]["capacity"].asInt();
				course->type = JsonCourseList[i]["type"].asString();
				course->price = JsonCourseList[i]["price"].asDouble();
				course->coach->id = JsonCourseList[i]["coach"]["id"].asInt();
				course->venue->id = JsonCourseList[i]["venue"]["id"].asInt();

				LOG(INFO)<<"course:"<<course->id;
				LOG(INFO)<<"course->venue:"<<course->venue->id;

				courseList->push_back(course);
			}
			courseDAO.addWeek(courseList.get());
			response(true);
		}else{
			LOG(ERROR)<<"json parse fail";
			response(false);
			return;
		}
	};

	(*webResource)["^/test/?$"]["GET"]=[](){

		response(true);

	};	


	return webResource;
}

