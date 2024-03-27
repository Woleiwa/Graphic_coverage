#pragma once
#ifndef _EDGE_H_
#define _EDGE_H_
#include"segment.h"
#include"vertice.h"
extern class Voronori_area;

class Edge : public Segment
{
public:
	Edge(Vertice* left, Vertice* right, Voronori_area* left_area, Voronori_area* right_area, int index);
	Edge(Voronori_area* left_area, Voronori_area* right_area, int index);
	int get_index() const;
	Vertice* get_left() const;
	Vertice* get_right() const;
private:
	int index;
	Vertice* left_vertice;
	Vertice* right_vertice;
	Voronori_area* left_area;
	Voronori_area* right_area;
};

Edge::Edge(Vertice* left, Vertice* right, Voronori_area* left_area, Voronori_area* right_area, int index)
{
	this->Segment::Segment(*left, *right);
	this->index = index;
	this->left_vertice = left;
	this->right_vertice = right;
	this->left_area = left_area;
	this->right_area = right_area;
}

Edge::Edge(Voronori_area* left_area, Voronori_area* right_area, int index)
{
	this->left_area = left_area;
	this->right_area = right_area;
	this->index = index;
	this->left_vertice = nullptr;
	this->right_vertice = nullptr;
}
#endif // !_EDGE_H_



