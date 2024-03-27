#include "point_event.h"
double Point_event::get_y() const
{
	this->site->get_y();
};

bool Point_event::get_type() const
{
	return POINT_EVENT;
};

Site* Point_event::get_site() const
{
	return this->site;
};