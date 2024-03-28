#pragma once
#ifndef _CIRCLE_EVENT_H_
#define _CIRCLE_EVENT_H_
#include "event.h"
#include "site.h"
#include "voronori_node.h"
class Circle_event : public Event
{
public:
	Circle_event(Site* site_1, Site* site_2, Site* site_3, Voronori_node* node);
	double get_y() const;
	bool get_type() const;
	Voronori_node* get_node() const;
	Point get_center() const;
	void disable();
	bool is_able() const;
	Site** get_sites() const;
	Site* get_central_site() const;
private:
	Site *site_1, *site_2, *site_3;
	Voronori_node* node;
	Point central_point, lowest_point;
	bool able = true;
};

Circle_event::Circle_event(Site* site_1, Site* site_2, Site* site_3, Voronori_node* node)
{
	this->site_1 = site_1;
	this->site_2 = site_2;
	this->site_3 = site_3;
	this->node = node;

	double gradient_1 = 0, gradient_2 = 0;
	double intersect_1 = 0, intersect_2 = 0;
	Point central_point1;
	Point central_point2;

	if (site_1->get_x() == site_2->get_x()) 
	{
		gradient_1 = site_1->get_gradient(*site_3);
		gradient_2 = site_2->get_gradient(*site_3);
		Point central_point1 = site_1->get_central(*site_3);
		Point central_point2 = site_2->get_central(*site_3);
	}
	else
	{
		if (site_2->get_x() == site_3->get_x()) 
		{
			gradient_1 = site_1->get_gradient(*site_2);
			gradient_2 = site_1->get_gradient(*site_3);
			Point central_point1 = site_1->get_central(*site_2);
			Point central_point2 = site_1->get_central(*site_3);
		}
		else
		{
			gradient_1 = site_1->get_gradient(*site_2);
			gradient_2 = site_2->get_gradient(*site_3);
			Point central_point1 = site_1->get_central(*site_2);
			Point central_point2 = site_2->get_central(*site_3);
		}
	}
	intersect_1 = central_point1.get_intersect_by_gradient(gradient_1);
	intersect_2 = central_point2.get_intersect_by_gradient(gradient_2);

	double x = (intersect_2 - intersect_1) / (gradient_1 - gradient_2);
	double y = gradient_1 * x + intersect_1;
	this->central_point = Point(x, y);
	double distance = central_point.get_distance(*site_1);
	this->lowest_point = Point(x, y - distance);
}
#endif // !_CIRCLE_EVENT_H_



