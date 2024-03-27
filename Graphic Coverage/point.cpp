#include "point.h"
#include<exception>
#include <math.h>

double Point::get_distance(const Point& another) const 
{
	double dx = this->x - another.x;
	double dy = this->y - another.y;
	double distance = pow(dx * dx + dy * dy, 0.5);
	return distance;
}

double Point::get_gradient(const Point& another) const
{
	double dx = this->x - another.x;
	if (dx == 0) {
		throw new std::exception("The divisor cannot be 0!");
	}
	double dy = this->y - another.y;
	return dy / dx;
}


double Point::get_x() const 
{
	return this->x;
}

double Point::get_y() const 
{
	return this->y;
}

double Point::get_intersect_by_gradient(double gradient) const
{
	return this->y - gradient * this->x;
}

Point Point::get_central(const Point& another) const
{
	double x = (this->x + another.x) / 2;
	double y = (this->y + another.y) / 2;
	Point point(x, y);
	return point;
};