#pragma once
#ifndef _SITE_H_
#define _SITE_H_
#include "point.h"
class Site : public Point
{
public:
	Site();
	Site(double x, double y, int index);
	bool operator<(const Site& another) const;
	bool operator==(const Site& another) const;
	int get_index() const;
	void modify_index(int index);
private:
	int index = -1;
};

Site::Site() {
	Point::Point();
};

Site::Site(double x, double y, int index) {
	Point::Point(x, y);
	this->index = index;
};

#endif // !_SITE_H_



