#include "../include/Model.h"

wyx::Venue::Venue():venue_type(make_shared<VenueType>()){}

wyx::Course::Course():venue(make_shared<Venue>()),coach(make_shared<Coach>()){}

wyx::Order::Order():member(make_shared<Member>()){}

wyx::CourseOrder::CourseOrder():course(make_shared<Course>()){}
