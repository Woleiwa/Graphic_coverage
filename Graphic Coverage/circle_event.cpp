#include "circle_event.h"

double Circle_event::get_y() const
{
	return this->lowest_point.get_y();
};

bool Circle_event::get_type() const
{
	return CIRCLE_EVENT;
};

void Circle_event::disable()
{
	this->able = false;
};

bool Circle_event::is_able() const
{
	return this->able;
};

Voronori_node* Circle_event::get_node() const
{
	return this->node;
}

Point Circle_event::get_center() const
{
	return this->central_point;
}