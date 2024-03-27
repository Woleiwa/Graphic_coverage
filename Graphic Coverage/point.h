#pragma once
#ifndef _POINT_H_
#define _POINT_H_
class Point
{
public:
	Point();
	Point(double x, double y);
	Point(const Point& another);
	double get_distance(const Point& another) const;
	double get_gradient(const Point& another) const;
	double get_x() const;
	double get_y() const;
	double get_intersect_by_gradient(double gradient) const;
	Point get_central(const Point& another) const;
	~Point();
protected:
	double x = 0, y = 0;
};

Point::Point() 
{
	this->x = 0;
	this->y = 0;
}

Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}

Point::Point(const Point& another) 
{
	this->x = another.x;
	this->y = another.y;
};

Point::~Point()
{
}
#endif // !
