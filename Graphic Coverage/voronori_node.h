#pragma once
#ifndef _VORONORI_NODE_H_
#define _VORONORI_NODE_H_
#include "site.h"
#include "event.h"
#include "edge.h"
class Voronori_node
{
public:
	Voronori_node(Site* left_site, Site* right_site, Event* event);
	bool is_leaf() const;
	void set_left_site(Site* left_site);
	void set_right_site(Site* right_site);
	void set_left_child(Voronori_node* left_child);
	void set_right_child(Voronori_node* right_child);
	void set_parent(Voronori_node* parent);
	void set_event(Event* event);
	void set_pre(Voronori_node* pre);
	void set_next(Voronori_node* next);
	void set_edge(Edge* edge);
	bool bigger(double x, double sweepline) const;
	bool smaller(double x, double sweepline) const;
	Voronori_node* get_left_child() const;
	Voronori_node* get_right_child() const;
	Voronori_node* get_parent() const;
	Voronori_node* get_pre() const;
	Voronori_node* get_next() const;
	Site* get_left_site() const;
	Site* get_right_site() const;
	Event* get_event() const;
	Edge* get_edge() const;
private: 
	Voronori_node* left_child;
	Voronori_node* right_child;
	Voronori_node* parent;
	Voronori_node* pre;
	Voronori_node* next;
	Edge* edge = nullptr;
	int balance_factor;
	Site* left_site;
	Site* right_site;
	Event* event;
	double calculate_pivot(double sweepline) const;
};

Voronori_node::Voronori_node(Site* left_site, Site* right_site, Event* event)
{
	this->left_site = left_site;
	this->right_site = right_site;
	this->right_child = nullptr;
	this->left_child = nullptr;
	this->parent = nullptr;
	this->pre = nullptr;
	this->next = nullptr;
	this->balance_factor = 0;
	this->event = event;
};
#endif // !_VORONORI_NODE_H_



