#pragma once

#ifndef _POINT_EVENT_H_
#define _POINT_EVENT_H_

#include "event.h"
#include "site.h"

class Point_event :public Event
{
public:
	Point_event(Site* site);
	double get_y() const;
	bool get_type() const;
	Site* get_site() const;
private:
	Site* site;
};

Point_event::Point_event(Site *site)
{
	this->site = site;
}
#endif
