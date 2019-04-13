#ifndef DAO_H
#define DAO_H

#include "DBConn.h"
#include "Model.h"
#include <vector>
#include <string>
#include <glog/logging.h>

namespace wyx{
	using namespace std;

	class MemberDAO{
		public:
			void add(Member *member);
			void update(Member *member);
			Member* get(int &id);
			Member* get(string &account);
			Member* get(string &account,string &password);
			vector<shared_ptr<Member>>* list();
	};

	class ManagerDAO{
		public:
			Manager* get(string &account,string &password);
	};

	class CoachDAO{
		public:
			void add(Coach *coach);
			void update(Coach *coach);
			Coach* get(int &id);
			vector<shared_ptr<Coach>>* list();
	};

	class VenueTypeDAO{
		public:
			VenueType* get(int &id);
			vector<shared_ptr<VenueType>>* list();
	};

	class VenueDAO{
		public:
			void add(Venue *Venue);
			void update(Venue *Venue);
			Venue* get(int &id);
			vector<shared_ptr<Venue>>* list();
	};

	class CourseDAO{
		public:
			void addWeek(vector<shared_ptr<Course>> * courseList);
			void add(Course * course);
			vector<shared_ptr<Course>>* getWeek(int start_date);
	};
}




#endif
