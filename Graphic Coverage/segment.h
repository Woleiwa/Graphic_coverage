#pragma once
#ifndef _SEGMENT_H_
#define _SEGMENT_H_
constexpr auto EPOSILON = 0.000001;
#include"point.h"

class Segment
{
public:
	Segment();
	Segment(Point& left, Point& right);
	Point* get_intersection(const Segment& another) const;
	bool on_line(const Point& point) const;
	double get_gradient() const;
	double get_intercept() const;
	bool is_vertical() const;
	~Segment();
protected:
	Point left = Point();
	Point right = Point();
};

Segment::Segment() 
{
	this->left = Point();
	this->right = Point();
}

Segment::Segment(Point& left, Point& right) 
{
	this->left = left;
	this->right = right;
}

Segment::~Segment() {

}

#endif 


