#include "segment.h"
#include <exception>

Point* Segment::get_intersection(const Segment& another) const 
{
	double x, y;// the x and y coordinaries of the intersection

	if (this->left.get_x() == this->right.get_y()) {
		if (another.left.get_x() == another.right.get_x()) 
		{
			return nullptr;
		}// these two Segments are both vertical to the X axis 
		x = this->left.get_x();
		double gradient = another.get_gradient();
		double intersect = another.get_intercept();
		y = gradient * x + intersect;
	}
	else if (another.left.get_x() == another.right.get_x()) 
	{
		x = another.left.get_x();
		double gradient = this->get_gradient();
		double intersect = this->get_intercept();
		y = gradient * x + intersect;
	}
	else 
	{
		double gradient_1 = this->get_gradient();
		double intersect_1 = this->get_intercept();
		double gradient_2 = another.get_gradient();
		double intersect_2 = another.get_intercept();
		double d_gradient = gradient_1 - gradient_2;
		if ((d_gradient <= EPOSILON && d_gradient >= -EPOSILON)){
			return nullptr;
		}// the two Segments are parallel to each other
		double d_intersect = intersect_2 - intersect_1;
		x = d_intersect / d_gradient;
		y = gradient_1 * x + intersect_2;
	}
	Point point(x, y);
	if (this->on_line(point)) {
		return new Point(point);
	}
	return nullptr;
};

bool Segment::on_line(const Point& point) const {

	// on the same Segment that is vertical to X axis
	if (point.get_x() == this->left.get_x() 
		&& point.get_x() == this->right.get_x())
	{
		if (point.get_y() >= this->left.get_y() && point.get_y() <= this->right.get_y()) {
			return true;
		}
		//the point should be between left_point and right_point
		return false;
	}

	//utilize the gradient of Segment(left, point) and Segment(right, point) to judge wether they are on the same Segment
	double gradient_1 = point.get_gradient(this->left);
	double gradient_2 = point.get_gradient(this->right);

	double d_gradient = gradient_1 - gradient_2;
	if ((d_gradient <= EPOSILON && d_gradient >= -EPOSILON)
		&&(point.get_x() >= this->left.get_x() && point.get_x() <= this->right.get_x()))// to eliminate the error caused by float calculation
	{
		return true;
	}
	//the point should be between left_point and right_point
	return false;
};

double Segment::get_gradient() const {
	try
	{
		return this->left.get_gradient(this->right);
	}
	catch (const std::exception& e)
	{
		throw std::exception("The Segment is vertical to X axis!");
	}
}

double Segment::get_intercept() const {
	try
	{
		double gradient = this->left.get_gradient(this->right);
		return this->left.get_intersect_by_gradient(gradient);
	}
	catch (const std::exception& e)
	{
		throw std::exception("The Segment is vertical to X axis!");
	}
}

bool Segment::is_vertical() const {
	return this->left.get_x() == this->right.get_x();
};