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

Site** Circle_event::get_sites() const
{
	Site** res = new Site * [3];
	res[0] = this->site_1;
	res[1] = this->site_2;
	res[2] = this->site_3;
	return res;
}

Site* Circle_event::get_central_site() const
{
	return this->node->get_right_site();
}