#pragma once
#ifndef _VORONORI_AREA_H_
#define _VORONORI_AREA_H_
#include"site.h"
#include"edge.h"
#include<vector>

class Voronori_area
{
public:
	Voronori_area(Site* site, std::vector<Edge*> edges);
	void add_edge(Edge* edge);
	Site* get_site() const;
	std::vector<Edge*> get_edges() const;
	Edge* seek_for_edge(Site* site) const;
	bool is_area_of(Site* site) const;
private:
	Site* site;
	std::vector<Edge*> edges;
};

Voronori_area::Voronori_area(Site* site, std::vector<Edge*> edges = std::vector<Edge*>())
{
	this->site = site;
	this->edges = edges;
}
#endif // !_VORONRORI_AREA_H_



