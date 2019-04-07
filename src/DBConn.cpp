#include "../include/DBConn.h"



#define DB_USER "root"  
#define DB_PASSWORD "123"  
#define DB_NAME "fmms"
#define DB_HOST "tcp://localhost:3306"  


sql::Driver* wyx::DBConn::driver = get_driver_instance();

std::string wyx::DBConn::test = "dsaf";

sql::Connection* getConnect(){
	std::cout<<wyx::DBConn::test;
	sql::Connection* conn = wyx::DBConn::driver->connect(DB_HOST,DB_USER,DB_PASSWORD);
	conn->setSchema(DB_NAME);
	return conn;
}

