#include "edge.h"
#include "site.h"
#include "voronori_area.h"

int Edge::get_index() const 
{
	return this->index;
}

Vertice* Edge::get_left() const
{
	return this->left_vertice;
};

Vertice* Edge::get_right() const
{
	return this->right_vertice;
};

bool Edge::edge_of_site(Site* site1, Site* site2) const
{
	if (this->left_area->is_area_of(site1) && this->right_area->is_area_of(site2))
	{
		return true;
	}
	else if (this->left_area->is_area_of(site2) && this->right_area->is_area_of(site1))
	{
		return true;
	}
	return false;
};

void Edge::set_vertice(Vertice* vertice)
{
	if (this->left_vertice == nullptr)
	{
		this->left_vertice = vertice;
		this->left = Point(*vertice);
	}
	else if(this->right_vertice == nullptr)
	{
		this->right_vertice = vertice;
		this->right = Point(*vertice);
	}
}