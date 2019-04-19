#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <memory>

namespace wyx{
	using namespace std;
	class Member{
		public:
			int id;
			string account;
			string password;
			string name;
			string sex;
			long start_date;
			long end_date;
	};

	class Manager{
		public:
			int id;
			string account;
			string password;
	};

	class Coach{
		public:
			int id;
			string name;
			string sex;
			long entry_date;
			string introduction;
			string status; //在职on_work 离职off_work
	};

	class VenueType{
		public:
			int id;
			string type;
	};

	class Venue{
		public:
			int id;
			string name;
			int capacity;
			string status;
			shared_ptr<VenueType> venue_type;

			Venue();
	};

	class Course{
		public:
			int id;
			long start_date;
			string start_hour;
			double price;
			int capacity;
			int registration_num;
			string type;
			shared_ptr<Venue> venue;
			shared_ptr<Coach> coach;

			Course();
	};

	class Order{
		public: 
			int id;
			shared_ptr<Member> member;
			long time;
			double price;

			Order();
	};


	class RenewOrder : public Order{
		public:
			long start_date;
			long end_date;
	};

	class CourseOrder : public Order{
		public:
			shared_ptr<Course> course;

			CourseOrder();
	};
}






#endif
