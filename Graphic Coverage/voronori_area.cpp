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

Edge* Voronori_area::seek_for_edge(Site* site) const
{
	Edge* target = nullptr;
	for (Edge* edge : this->edges)
	{
		if (edge->edge_of_site(this->site, site))
		{
			target = edge;
			break;
		}
	}
	return target;
}

bool Voronori_area::is_area_of(Site* site) const
{
	return this->site == site;
};