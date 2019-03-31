#ifndef MANAGER_SESSION_H
#define MANAGER_SESSION_H

#include <string>
#include <hiredis/hiredis.h>
#include "Manager.h"


using namespace std;

class ManagerSession{
	private:
		struct timeval timeout = {2, 0};    //2s的超时时间
		const string ip = "localhost";
		const unsigned short port = 6379;  
		const unsigned long expire_time = 24*60*60;

		redisContext *pRedisContext;
		redisReply *pRedisReply;


	public:
		Manager* getManager(){
			string cookie = getenv("HTTP_COOKIE");

			return nullptr;
		}
};





#endif
