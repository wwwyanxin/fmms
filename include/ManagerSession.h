#ifndef MANAGER_SESSION_H
#define MANAGER_SESSION_H

#include <string>
#include <hiredis/hiredis.h>
#include "Manager.h"
#include "util.h"


using namespace std;

class ManagerSession{
	private:
		struct timeval timeout = {2, 0};    //2s的超时时间
		const string ip = "localhost";
		const unsigned short port = 6379;  
		const unsigned long expire_time = 24*60*60;
		const string sessionCookieKey = "manager_id";

		redisContext *pRedisContext;
		redisReply *pRedisReply;


	public:
		Manager* getManager(){
			string cookieStr = getenv("HTTP_COOKIE");
			shared_ptr<string> sessionCookieValue(wyx::getParamValue(cookieStr,sessionCookieKey,"; "));

			return nullptr;
		}

//		void setManager(Manager &manager){

//		}
};





#endif
