#pragma once
#ifndef _VERTICE_H_
#define _VERTICE_H_
#include "point.h"
#include <vector>
extern class Edge;
class Vertice : public Point
{
public:
	Vertice();
	Vertice(double x, double y, std::vector<Edge*> edge_list, int index, bool on_boundary);
	int get_index() const;
	std::vector<Edge*> get_edge_list() const;
	void add_edge(Edge* edge);
private:
	bool on_boundary;
	std::vector<Edge*> edge_list;
	int index;
};

Vertice::Vertice() 
{
	this->Point::Point();
	this->index = 1;
	this->on_boundary = false;
	this->edge_list = std::vector<Edge*>();
}

Vertice::Vertice(double x, double y, std::vector<Edge*> edge_list, int index, bool on_boundary)
{
	this->Point::Point(x, y);
	this->edge_list = edge_list;
	this->index = index;
	this->on_boundary = on_boundary;
}
#endif // !_EDGE_H_



