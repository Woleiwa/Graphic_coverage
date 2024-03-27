#pragma once
#ifndef _PARABOLA_H_
#define _PARABOLA_H_
#include <cmath>
#include<utility>

class Parabola
{
public:
	Parabola(double a, double b, double c);
	Parabola(std::pair<double, double> focus, double focal_line);
	std::pair<double, double> get_intersect(const Parabola &another) const;
	double get_y(double x)const;
	double get_a() const;
	double get_b() const;
	double get_c() const;
private:
	double a, b, c;
};

Parabola::Parabola(double a, double b, double c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}

Parabola::Parabola(std::pair<double, double> focus, double focal_line)
{
	double a = focus.first;
	double b = focus.second;
	double c = focal_line;
	this->a = 1.0 / 2 * (b - c);
	this->b = - a / (b - c);
	this->c = (pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * b - 2 * c);
}
#endif // !_PARABOLA_H_



