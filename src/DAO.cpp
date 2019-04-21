#include "../include/DAO.h"
#include <memory>


using namespace wyx;

void daoExceptionCatch(sql::SQLException &e){
	LOG(ERROR) << "# ERR: SQLException in " << __FILE__;
	LOG(ERROR) << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
	LOG(ERROR) << "# ERR: " << e.what();
	LOG(ERROR) << " (MySQL error code: " << e.getErrorCode();
	LOG(ERROR) << ", SQLState: " << e.getSQLState() << " )" << std::endl;
}

void MemberDAO::add(Member *member){
	string sql_str="insert into member(`name`,`account`,`password`,`sex`,`start_date`,`end_date`) values(?,?,?,?,?,?);";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setString(1,member->name);
		pstmt->setString(2,member->account);
		pstmt->setString(3,member->password);
		pstmt->setString(4,member->sex);
		pstmt->setInt(5,member->start_date);
		pstmt->setInt(6,member->end_date);

		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return;
}

void MemberDAO::update(Member *member){
	string sql_str="update member set `name`=?,`account`=?,`password`=?,`sex`=?,`start_date`=?,`end_date`=? where id=?;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setString(1,member->name);
		pstmt->setString(2,member->account);
		pstmt->setString(3,member->password);
		pstmt->setString(4,member->sex);
		pstmt->setInt(5,member->start_date);
		pstmt->setInt(6,member->end_date);
		pstmt->setInt(7,member->id);

		LOG(INFO)<<"member->end_date="<<member->end_date;
		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return;
}

Member* MemberDAO::get(string &account){
	Member* member = nullptr;
	string sql_str="select * from member where `account`=?;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setString(1,account);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		if(res->next()){
			member = new Member();
			member->id = res->getInt("id");
			member->name = res->getString("name");
			member->account = res->getString("account");
			member->password = res->getString("password");
			member->sex = res->getString("sex");
			member->start_date = res->getInt("start_date");
			member->end_date = res->getInt("end_date");
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return member;
}


Member* MemberDAO::get(string &account,string &password){
	Member* member = nullptr;
	string sql_str="select * from member where `account`=? and password=?;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setString(1,account);
		pstmt->setString(2,password);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		if(res->next()){
			member = new Member();
			member->id = res->getInt("id");
			member->name = res->getString("name");
			member->account = res->getString("account");
			member->password = res->getString("password");
			member->sex = res->getString("sex");
			member->start_date = res->getInt("start_date");
			member->end_date = res->getInt("end_date");
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return member;
}

vector<shared_ptr<Member>>* MemberDAO::list(){
	auto memberList = new vector<shared_ptr<Member>>;
	string sql_str="select * from member;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		while(res->next()){
			auto member = make_shared<Member>();
			member->id = res->getInt("id");
			member->name = res->getString("name");
			member->account = res->getString("account");
			member->password = res->getString("password");
			member->sex = res->getString("sex");
			member->start_date = res->getInt("start_date");
			member->end_date = res->getInt("end_date");

			memberList->push_back(member);
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return memberList;
}

Manager* ManagerDAO::get(string &account,string &password){
	Manager* manager = nullptr;
	string sql_str="select * from manager where `account`=? and password=?;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setString(1,account);
		pstmt->setString(2,password);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		if(res->next()){
			manager = new Manager();
			manager->id = res->getInt("id");
			manager->account = res->getString("account");
			manager->password = res->getString("password");
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return manager;
}

void CoachDAO::add(Coach *coach){
	string sql_str="insert into coach(`name`,`sex`,`entry_date`,`introduction`,`status`) values(?,?,?,?,?);";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setString(1,coach->name);
		pstmt->setString(2,coach->sex);
		pstmt->setInt(3,coach->entry_date);
		pstmt->setString(4,coach->introduction);
		pstmt->setString(5,coach->status);

		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return;
}

void CoachDAO::update(Coach *coach){
	string sql_str="update coach set `name`=?,`sex`=?,`entry_date`=?,`introduction`=?,`status`=? where id=?;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setString(1,coach->name);
		pstmt->setString(2,coach->sex);
		pstmt->setInt(3,coach->entry_date);
		pstmt->setString(4,coach->introduction);
		pstmt->setString(5,coach->status);
		pstmt->setInt(6,coach->id);

		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return;
}

Coach* CoachDAO::get(int &id){
	Coach* coach = nullptr;
	string sql_str="select * from coach where `id`=?;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,id);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		if(res->next()){
			coach = new Coach();
			coach->id = res->getInt("id");
			coach->name = res->getString("name");
			coach->sex = res->getString("sex");
			coach->entry_date = res->getInt("entry_date");
			coach->introduction = res->getString("introduction");
			coach->status = res->getString("status");
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return coach;
}

vector<shared_ptr<Coach>>* CoachDAO::list(){
	auto coachList = new vector<shared_ptr<Coach>>;

	string sql_str="select * from coach;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		while(res->next()){
			auto coach = make_shared<Coach>();
			coach->id = res->getInt("id");
			coach->name = res->getString("name");
			coach->sex = res->getString("sex");
			coach->entry_date = res->getInt("entry_date");
			coach->introduction = res->getString("introduction");
			coach->status = res->getString("status");

			coachList->push_back(coach);
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return coachList;
}

VenueType* VenueTypeDAO::get(int &id){
	VenueType* venue_type = nullptr;
	string sql_str="select * from venue_type where `id`=?;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,id);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		if(res->next()){
			venue_type = new VenueType();
			venue_type->id = res->getInt("id");
			venue_type->type = res->getString("type");
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return venue_type;
}

vector<shared_ptr<VenueType>>* VenueTypeDAO::list(){
	auto venue_type_list = new vector<shared_ptr<VenueType>>;

	string sql_str="select * from venue_type;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		while(res->next()){
			auto venue_type = make_shared<VenueType>();
			venue_type->id = res->getInt("id");
			venue_type->type = res->getString("type");

			venue_type_list->push_back(venue_type);
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return venue_type_list;
}

void VenueDAO::add(Venue *venue){
	string sql_str="insert into venue(`name`,`capacity`,`status`,`type_id`) values(?,?,?,?);";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setString(1,venue->name);
		pstmt->setInt(2,venue->capacity);
		pstmt->setString(3,venue->status);
		pstmt->setInt(4,venue->venue_type->id);

		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return;
}

void VenueDAO::update(Venue *venue){
	string sql_str="update venue set `name`=?,`capacity`=?,`status`=?,`type_id`=? where id=?;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setString(1,venue->name);
		pstmt->setInt(2,venue->capacity);
		pstmt->setString(3,venue->status);
		pstmt->setInt(4,venue->venue_type->id);
		pstmt->setInt(5,venue->id);
		
		/*
		LOG(INFO)<<"name="<<venue->name;
		LOG(INFO)<<"capacity="<<venue->capacity;
		LOG(INFO)<<"status="<<venue->status;
		LOG(INFO)<<"venue_type.id="<<venue->venue_type->id;
		LOG(INFO)<<"id="<<venue->id;
		*/


		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return;
}

Venue* VenueDAO::get(int &id){
	Venue* venue = nullptr;
	string sql_str="select venue.*,venue_type.type as `venue_type.type` from venue,venue_type where venue.id=? and venue.type_id=venue_type.id;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,id);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		if(res->next()){
			venue = new Venue();
			venue->id = res->getInt("id");
			venue->name = res->getString("name");
			venue->capacity = res->getInt("capacity");
			venue->status = res->getString("status");

			venue->venue_type = make_shared<VenueType>();
			venue->venue_type->id = stoi(res->getString("type_id"));
			venue->venue_type->type = res->getString("venue_type.type");
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return venue;
}

vector<shared_ptr<Venue>>* VenueDAO::list(){
	auto venueList = new vector<shared_ptr<Venue>>;

	string sql_str="select venue.*,venue_type.type as `venue_type.type` from venue,venue_type where venue.type_id=venue_type.id;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		while(res->next()){
			auto venue = make_shared<Venue>();

			venue->id = res->getInt("id");
			venue->name = res->getString("name");
			venue->capacity = res->getInt("capacity");
			venue->status = res->getString("status");

			venue->venue_type = make_shared<VenueType>();
			venue->venue_type->id = stoi(res->getString("type_id"));
			venue->venue_type->type = res->getString("venue_type.type");

			venueList->push_back(venue);
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return venueList;
}

void CourseDAO::add(Course * course){
	string sql_str="insert into course(`start_date`,`start_hour`,`price`,`capacity`,`registration_num`,`type`,`venue_id`,`coach_id`) values(?,?,?,?,?,?,?,?);";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,course->start_date);
		pstmt->setString(2,course->start_hour);
		pstmt->setDouble(3,course->price);
		pstmt->setInt(4,course->capacity);
		pstmt->setInt(5,course->registration_num);
		pstmt->setString(6,course->type);
		pstmt->setInt(7,course->venue->id);
		pstmt->setInt(8,course->coach->id);

		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return;
}

void CourseDAO::addWeek(vector<shared_ptr<Course>> *courseList){
	for(auto &item : *courseList){
		this->add(item.get());
	}
}

void CourseDAO::update(Course * course){
	string sql_str="update course set `start_date`=?,`start_hour`=?,`price`=?,`capacity`=?,`registration_num`=?,`type`=?,`venue_id`=?,`coach_id`=? where id=?;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,course->start_date);
		pstmt->setString(2,course->start_hour);
		pstmt->setDouble(3,course->price);
		pstmt->setInt(4,course->capacity);
		pstmt->setInt(5,course->registration_num);
		pstmt->setString(6,course->type);
		pstmt->setInt(7,course->venue->id);
		pstmt->setInt(8,course->coach->id);
		pstmt->setInt(9,course->id);

		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return;
}

vector<shared_ptr<Course>>* CourseDAO::getWeek(int start_date){
	auto courseList = new vector<shared_ptr<Course>>;
	string sql_str="select  \
		course.*, \
		coach.id as `coach.id` , \
		coach.name as `coach.name` , \
		coach.sex as `coach.sex`, \
		coach.`status` as `coach.status`, \
		coach.introduction as `coach.introduction`, \
		coach.entry_date as `coach.entry_date`, \
		venue_type.id as `venue_type.id`, \
		venue_type.type as `venue_type.type`, \
		venue.id as `venue.id`, \
		venue.`status` as `venue.status`, \
		venue.`name` as `venue.name`, \
		venue.capacity as `venue.capacity`, \
		venue.type_id as `venue.type_id` \
		from course,venue,venue_type,coach \
		where start_date=? and course.venue_id = venue.id and course.coach_id = coach.id and venue.type_id = venue_type.id;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,start_date);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		while(res->next()){
			auto course = make_shared<Course>();
			course->id = res->getInt("id");
			course->start_date = res->getInt("start_date");
			course->start_hour = res->getString("start_hour");
			course->price = res->getDouble("price");
			course->capacity = res->getInt("capacity");
			course->registration_num = res->getInt("registration_num");
			course->type = res->getString("type");

			course->venue->id = res->getInt("venue.id");
			course->venue->name = res->getString("venue.name");
			course->venue->capacity = res->getInt("venue.capacity");
			course->venue->status = res->getString("venue.status");

			course->venue->venue_type->id = res->getInt("venue_type.id");
			course->venue->venue_type->type = res->getString("venue_type.type");

			course->coach->id = res->getInt("coach.id");
			course->coach->name = res->getString("coach.name");
			course->coach->entry_date = res->getInt("coach.entry_date");
			course->coach->status = res->getString("coach.status");
			course->coach->sex = res->getString("coach.sex");
			course->coach->introduction = res->getString("coach.introduction");


			courseList->push_back(course);
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return courseList;
}

Course* CourseDAO::get(int id){
	auto course = new Course();
	string sql_str="select  \
		course.*, \
		coach.id as `coach.id` , \
		coach.name as `coach.name` , \
		coach.sex as `coach.sex`, \
		coach.`status` as `coach.status`, \
		coach.introduction as `coach.introduction`, \
		coach.entry_date as `coach.entry_date`, \
		venue_type.id as `venue_type.id`, \
		venue_type.type as `venue_type.type`, \
		venue.id as `venue.id`, \
		venue.`status` as `venue.status`, \
		venue.`name` as `venue.name`, \
		venue.capacity as `venue.capacity`, \
		venue.type_id as `venue.type_id` \
		from course,venue,venue_type,coach \
		where course.id=? and course.venue_id = venue.id and course.coach_id = coach.id and venue.type_id = venue_type.id;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,id);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		if(res->next()){
			course->id = res->getInt("id");
			course->start_date = res->getInt("start_date");
			course->start_hour = res->getString("start_hour");
			course->price = res->getDouble("price");
			course->capacity = res->getInt("capacity");
			course->registration_num = res->getInt("registration_num");
			course->type = res->getString("type");

			course->venue->id = res->getInt("venue.id");
			course->venue->name = res->getString("venue.name");
			course->venue->capacity = res->getInt("venue.capacity");
			course->venue->status = res->getString("venue.status");

			course->venue->venue_type->id = res->getInt("venue_type.id");
			course->venue->venue_type->type = res->getString("venue_type.type");

			course->coach->id = res->getInt("coach.id");
			course->coach->name = res->getString("coach.name");
			course->coach->entry_date = res->getInt("coach.entry_date");
			course->coach->status = res->getString("coach.status");
			course->coach->sex = res->getString("coach.sex");
			course->coach->introduction = res->getString("coach.introduction");

		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return course;
}


void RenewOrderDAO::add(RenewOrder * renewOrder){
	string sql_str="insert into renew_order(`member_id`,`time`,`price`,`start_date`,`end_date`) values(?,?,?,?,?);";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,renewOrder->member->id);
		pstmt->setInt(2,renewOrder->time);
		pstmt->setDouble(3,renewOrder->price);
		pstmt->setInt(4,renewOrder->start_date);
		pstmt->setInt(5,renewOrder->end_date);

		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return;
}


vector<shared_ptr<RenewOrder>>* RenewOrderDAO::listByMemberId(int member_id){
	auto renewOrderList = new vector<shared_ptr<RenewOrder>>;

	string sql_str="select renew_order.*, \
					member.id as `member.id`, \
					member.name as `member.name`, \
					member.account as `member.account`, \
					member.password as `member.password`, \
					member.sex as `member.sex`, \
					member.start_date as `member.start_date`, \
					member.end_date as `member.end_date` \
					from renew_order,member  \
					where member.id = ? and renew_order.member_id = member.id;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,member_id);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		while(res->next()){
			auto renewOrder = make_shared<RenewOrder>();

			renewOrder->id = res->getInt("id");
			renewOrder->time = res->getInt("time");
			renewOrder->price = res->getDouble("price");
			renewOrder->start_date = res->getInt("start_date");
			renewOrder->end_date = res->getInt("end_date");
			
			renewOrder->member->id = res->getInt("member.id");
			renewOrder->member->name = res->getString("member.name");
			renewOrder->member->account = res->getString("member.account");
			renewOrder->member->password = res->getString("member.password");
			renewOrder->member->sex = res->getString("member.sex");
			renewOrder->member->start_date = res->getInt("member.start_date");
			renewOrder->member->end_date = res->getInt("member.end_date");

			renewOrderList->push_back(renewOrder);

		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return renewOrderList;
}

vector<shared_ptr<RenewOrder>>* RenewOrderDAO::list(){
	auto renewOrderList = new vector<shared_ptr<RenewOrder>>;

	string sql_str="select renew_order.*, \
					member.id as `member.id`, \
					member.name as `member.name`, \
					member.account as `member.account`, \
					member.password as `member.password`, \
					member.sex as `member.sex`, \
					member.start_date as `member.start_date`, \
					member.end_date as `member.end_date` \
					from renew_order,member  \
					where renew_order.member_id = member.id;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));


		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		while(res->next()){
			auto renewOrder = make_shared<RenewOrder>();

			renewOrder->id = res->getInt("id");
			renewOrder->time = res->getInt("time");
			renewOrder->price = res->getDouble("price");
			renewOrder->start_date = res->getInt("start_date");
			renewOrder->end_date = res->getInt("end_date");
			
			renewOrder->member->id = res->getInt("member.id");
			renewOrder->member->name = res->getString("member.name");
			renewOrder->member->account = res->getString("member.account");
			renewOrder->member->password = res->getString("member.password");
			renewOrder->member->sex = res->getString("member.sex");
			renewOrder->member->start_date = res->getInt("member.start_date");
			renewOrder->member->end_date = res->getInt("member.end_date");

			renewOrderList->push_back(renewOrder);

		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return renewOrderList;
}

void CourseOrderDAO::add(CourseOrder * courseOrder){
	string sql_str="insert into course_order(`member_id`,`time`,`price`,`course_id`) values(?,?,?,?);";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,courseOrder->member->id);
		pstmt->setInt(2,courseOrder->time);
		pstmt->setDouble(3,courseOrder->price);
		pstmt->setInt(4,courseOrder->course->id);
		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return;
}

int CourseOrderDAO::countOfMemberAndCourse(int order_id,int member_id){
	string sql_str="select count(*) from course_order where course_id=? and member_id=?;";

	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,order_id);
		pstmt->setInt(2,member_id);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";


		if(res->next()){
			return res->getInt(1);
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return 0;
}

vector<shared_ptr<CourseOrder>>* CourseOrderDAO::list(){
	auto courseOrderList = new vector<shared_ptr<CourseOrder>>;
	string sql_str="select course_order.*, \
					member.id as `member.id`, \
					member.name as `member.name`, \
					member.account as `member.account`, \
					member.password as `member.password`, \
					member.sex as `member.sex`, \
					member.start_date as `member.start_date`, \
					member.end_date as `member.end_date` \
					from course_order,member \
					where course_order.member_id = member.id;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		auto courseDAO = make_shared<CourseDAO>();

		while(res->next()){
			auto courseOrder = make_shared<CourseOrder>();

			courseOrder->id = res->getInt("id");
			courseOrder->time = res->getInt("time");
			courseOrder->price = res->getDouble("price");
			
			courseOrder->member->id = res->getInt("member.id");
			courseOrder->member->name = res->getString("member.name");
			courseOrder->member->account = res->getString("member.account");
			courseOrder->member->password = res->getString("member.password");
			courseOrder->member->sex = res->getString("member.sex");
			courseOrder->member->start_date = res->getInt("member.start_date");
			courseOrder->member->end_date = res->getInt("member.end_date");
			courseOrder->course.reset(courseDAO->get(res->getInt("course_id")));


			courseOrderList->push_back(courseOrder);
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return courseOrderList;
}

vector<shared_ptr<CourseOrder>>* CourseOrderDAO::listByMemberId(int member_id){
	auto courseOrderList = new vector<shared_ptr<CourseOrder>>;
	string sql_str="select course_order.*, \
					member.id as `member.id`, \
					member.name as `member.name`, \
					member.account as `member.account`, \
					member.password as `member.password`, \
					member.sex as `member.sex`, \
					member.start_date as `member.start_date`, \
					member.end_date as `member.end_date` \
					from course_order,member \
					where member.id=? and course_order.member_id = member.id;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,member_id);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		auto courseDAO = make_shared<CourseDAO>();

		while(res->next()){
			auto courseOrder = make_shared<CourseOrder>();

			courseOrder->id = res->getInt("id");
			courseOrder->time = res->getInt("time");
			courseOrder->price = res->getDouble("price");
			
			courseOrder->member->id = res->getInt("member.id");
			courseOrder->member->name = res->getString("member.name");
			courseOrder->member->account = res->getString("member.account");
			courseOrder->member->password = res->getString("member.password");
			courseOrder->member->sex = res->getString("member.sex");
			courseOrder->member->start_date = res->getInt("member.start_date");
			courseOrder->member->end_date = res->getInt("member.end_date");
			courseOrder->course.reset(courseDAO->get(res->getInt("course_id")));


			courseOrderList->push_back(courseOrder);
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return courseOrderList;
}

vector<shared_ptr<CourseOrder>>* CourseOrderDAO::listByCourseId(int course_id){
	auto courseOrderList = new vector<shared_ptr<CourseOrder>>;
	string sql_str="select course_order.*, \
					member.id as `member.id`, \
					member.name as `member.name`, \
					member.account as `member.account`, \
					member.password as `member.password`, \
					member.sex as `member.sex`, \
					member.start_date as `member.start_date`, \
					member.end_date as `member.end_date` \
					from course_order,member \
					where course_order.course_id=? and course_order.member_id = member.id;";
	shared_ptr<sql::Connection> conn;
	shared_ptr<sql::PreparedStatement> pstmt;
	shared_ptr<sql::ResultSet> res;

	try{
		conn.reset(DBConn::getConnect());
		pstmt.reset(conn->prepareStatement(sql_str));

		pstmt->setInt(1,course_id);

		res.reset(pstmt->executeQuery());

		LOG(INFO)<<"sql execute success";

		auto courseDAO = make_shared<CourseDAO>();

		while(res->next()){
			auto courseOrder = make_shared<CourseOrder>();

			courseOrder->id = res->getInt("id");
			courseOrder->time = res->getInt("time");
			courseOrder->price = res->getDouble("price");
			
			courseOrder->member->id = res->getInt("member.id");
			courseOrder->member->name = res->getString("member.name");
			courseOrder->member->account = res->getString("member.account");
			courseOrder->member->password = res->getString("member.password");
			courseOrder->member->sex = res->getString("member.sex");
			courseOrder->member->start_date = res->getInt("member.start_date");
			courseOrder->member->end_date = res->getInt("member.end_date");
			courseOrder->course.reset(courseDAO->get(res->getInt("course_id")));


			courseOrderList->push_back(courseOrder);
		}

	} catch (sql::SQLException& e) {
		daoExceptionCatch(e);
	}
	return courseOrderList;
}

