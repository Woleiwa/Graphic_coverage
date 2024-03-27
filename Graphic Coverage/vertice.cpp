#include "vertice.h"
#include "edge.h"

int Vertice::get_index() const 
{
	return this->index;
};

std::vector<Edge*>  Vertice::get_edge_list() const
{
	return this->edge_list;
};

void Vertice::add_edge(Edge* edge)
{
	for (Edge* element : this->edge_list) 
	{
		if (element->get_index() == edge->get_index()) 
			return;
	}
	this->edge_list.push_back(edge);
};