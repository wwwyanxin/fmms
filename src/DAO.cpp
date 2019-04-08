#include "../include/DAO.h"
#include <memory>
#include <time.h>


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

		pstmt->setString(1,"张三");
		pstmt->setString(2,"wyx123213");
		pstmt->setString(3,"jyhufasf");
		pstmt->setString(4,"male");
		time_t now_time = time(nullptr);
		pstmt->setInt(5,now_time);
		pstmt->setInt(6,now_time + 30*24*60*60);

		//res.reset(pstmt->executeQuery());
		pstmt->executeUpdate();

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


