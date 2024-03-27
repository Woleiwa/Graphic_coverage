#pragma once
#ifndef _BOUNDARY_H_
#define _BOUNDARY_H_
#include "point.h"
#include "segment.h"
#include <list>
class Boundary: public Segment
{
public:
	Boundary(Point& left, Point& right);
private:
	bool is_vertical;
};

Boundary::Boundary(Point& left, Point& right)
{
	Segment::Segment(left, right);
	if (left.get_x() == right.get_x()) {
		is_vertical = false;
	}
	else
	{
		is_vertical = true;
	}
}
#endif


