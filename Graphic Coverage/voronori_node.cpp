#include "voronori_node.h"
#include <utility>
#include "parabola.h"

bool Voronori_node::is_leaf() const
{
	return *(this->left_site) == *(this->right_site);
};

void Voronori_node::set_left_child(Voronori_node* left_child) 
{
	this->left_child = left_child;
	left_child->set_parent(this);
};

void Voronori_node::set_right_child(Voronori_node* right_child)
{
	this->right_child = right_child;
	right_child->set_parent(this);
};

void Voronori_node::set_parent(Voronori_node* parent)
{
	this->parent = parent;
};

void Voronori_node::set_event(Event* event)
{
	this->event = event;
}

bool Voronori_node::bigger(double x, double sweepline) const
{
	double pivot = this->calculate_pivot(sweepline);
	return pivot > x;
};

bool Voronori_node::smaller(double x, double sweepline) const
{
	double pivot = this->calculate_pivot(sweepline);
	return pivot < x;
};
  
double Voronori_node::calculate_pivot(double sweepline) const
{
	std::pair<double, double> focus_1 = std::make_pair(this->left_site->get_x(), this->left_site->get_y());
	std::pair<double, double> focus_2 = std::make_pair(this->right_site->get_x(), this->right_site->get_y());

	Parabola parabola_1 = Parabola(focus_1, sweepline);
	Parabola parabola_2 = Parabola(focus_2, sweepline);

	std::pair<double, double> inter_x = parabola_1.get_intersect(parabola_2);

	double judge = parabola_1.get_a() - parabola_2.get_a();
	double pivot = inter_x.second;
	if (judge < 0)
	{
		pivot = inter_x.first;
	}
	return pivot;
}

Voronori_node* Voronori_node::get_left_child() const
{
	return this->left_child;
};

Voronori_node* Voronori_node::get_right_child() const
{
	return this->right_child;
};

Voronori_node* Voronori_node::get_parent() const
{
	return this->parent;
};

Site* Voronori_node::get_left_site() const
{
	return this->left_site;
};

Site* Voronori_node::get_right_site() const
{
	return this->right_site;
};

Event* Voronori_node::get_event() const
{
	return this->event;
}

void Voronori_node::set_pre(Voronori_node* pre)
{
	if (this->is_leaf())
	{
		this->pre = pre;
	}
};

void Voronori_node::set_next(Voronori_node* next)
{
	if (this->is_leaf())
	{
		this->next = next;
	}
};

Voronori_node* Voronori_node::get_pre() const
{
	return this->pre;
}

Voronori_node* Voronori_node::get_next() const
{
	return this->next;
}