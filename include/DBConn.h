#ifndef DBCONN_H
#define DBCONN_H


#include<iostream>

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

namespace wyx{
	class DBConn{
		private:
			static sql::Driver *driver;
		public:
			static sql::Connection* getConnect();
	};
}

#endif
