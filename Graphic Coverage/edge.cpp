#include "edge.h"

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


