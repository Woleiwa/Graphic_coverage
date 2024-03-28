#pragma once
#ifndef _VORONORI_H_
#define _VORONORI_H_

#include"edge.h"
#include"vertice.h"
#include"boundary.h"
#include"site.h"
#include"voronori_area.h"
#include"voronori_node.h"
#include"event.h"
#include"circle_event.h"
#include"point_event.h"
#include<vector>
#include<queue>

class Voronori
{
public:
	Voronori(double width, double length, double radius);
	static bool coverable(double width, double length, double radius) { return !(width > 2 * radius && length > 2 * radius); };
	void add_site(Site site);
	void generate_voronori();
	bool all_covered() const;
	void search_and_insert(Site* site);
	std::vector<Vertice*> get_vertice_list() const;
	std::vector<Edge*> get_edge_list() const;
	std::vector<Site*> get_site_list() const;
	std::vector<Boundary*> get_boundary_list() const;
	void handle_point_event(Point_event* p_event);
	void handle_circle_event(Circle_event* c_event);
private:
	double width, length, radius;
	std::vector<Edge*> edge_list;
	std::vector<Vertice*> vertice_list;
	std::vector<Boundary*> boundary_list;
	std::vector<Site*> site_list;
	std::vector<Voronori_area*> voronori_area_list;
	std::priority_queue<Event*> event_queue;
	Voronori_node* root;
	void clear_tree();
	Voronori_node* seek_for_common_ancestor(Voronori_node* pre, Voronori_node* next);
};

Voronori::Voronori(double width, double length, double radius)
{
	this->width = width;
	this->length = length;
	this->radius = radius;
	Point point_1(0, 0);
	Point point_2(0, length);
	Point point_3(width, 0);
	Point point_4(width, length);
	Boundary* boudary_1 = new Boundary(point_1, point_2);
	Boundary* boudary_2 = new Boundary(point_1, point_3);
	Boundary* boudary_3 = new Boundary(point_2, point_4);
	Boundary* boudary_4 = new Boundary(point_3, point_4);

	this->boundary_list = std::vector<Boundary*>();
	this->edge_list = std::vector<Edge*>();
	this->site_list = std::vector<Site*>();
	this->vertice_list = std::vector<Vertice*>();

	this->boundary_list.push_back(boudary_1);
	this->boundary_list.push_back(boudary_2);
	this->boundary_list.push_back(boudary_3);
	this->boundary_list.push_back(boudary_4);

	this->site_list = std::vector<Site*>();
	this->edge_list = std::vector<Edge*>();
	this->vertice_list = std::vector<Vertice*>();
	this->event_queue = std::priority_queue<Event*>();
	this->voronori_area_list = std::vector<Voronori_area*>();
	this->root = nullptr;
}

#endif // !_VORONORI_H_




