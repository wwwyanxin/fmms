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

		//time_t now_time = time(nullptr);

		pstmt->setInt(5,member->start_date);
		pstmt->setInt(6,member->end_date);

		//res.reset(pstmt->executeQuery());
		pstmt->executeUpdate();

		LOG(INFO)<<"sql execute success";

		/*
		while (res->next()){
			LOG(INFO)<<"res->next();";
			string str_res = res->getString("name");
			string account = res->getString("start_date");
			cout<<"account: "<<account<<endl;
			cout << "QueryRes: " <<str_res<<endl;
			cout<<endl;
		}
		*/

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
