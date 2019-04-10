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

