#include "voronori_area.h"

void Voronori_area::add_edge(Edge* edge)
{
	this->edges.push_back(edge);
};

Site* Voronori_area::get_site() const
{
	return this->site;
};

std::vector<Edge*> Voronori_area::get_edges() const
{
	return this->edges;
};