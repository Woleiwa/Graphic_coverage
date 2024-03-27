#include "parabola.h"

std::pair<double, double> Parabola::get_intersect(const Parabola& another) const
{
	double a = this->a - another.a;
	double b = this->b - another.b;
	double c = this->c - another.c;
	double x1 = 0;
	double x2 = 0;
	if (a != 0)
	{
		double judge = pow(b, 2) - 4 * a * c;
		x1 = (-b + pow(judge, 1 / 2)) / 2 * a;
		x2 = (-b - pow(judge, 1 / 2)) / 2 * a;
	}
	else
	{
		x1 = x2 = -c / b;
	}
	return std::make_pair(x1, x2);
};

double Parabola::get_y (double x)const
{
	double y = this->a * pow(x, 2) + this->b * x + this->c;
	return y;
};

double Parabola::get_a() const
{
	return this->a;
};

double Parabola::get_b() const
{
	return this->b;
};

double Parabola::get_c() const
{
	return this->c;
};