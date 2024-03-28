#include "voronori.h"
#include "point_event.h"
#include <map>
#include <exception>

void Voronori::add_site(Site site)
{
	int length = this->site_list.size();
	int insert_index = 0;

	if (site < *(this->site_list[0]))
	{
		insert_index = 0;
	}
	else if(*(this->site_list[length - 1]) < site)
	{
		insert_index = length;
	}
	else
	{
		int start = 0, end = length - 1;
		int mid = (start + end) / 2;
		while (start < end)
		{
			if (*(this->site_list[mid]) < site && site < *(this->site_list[mid + 1]))
			{
				insert_index = mid + 1;
				break;
			}
			else if (site < *(this->site_list[mid]))
			{
				end = mid - 1;
			}
			else
			{
				start = mid + 1;
			}
			mid = (start + end) / 2;
		}
	}

	Site* new_site = new Site(site.get_x(), site.get_y(), insert_index);
	this->site_list.push_back(new_site);

	for (int i = length; i > insert_index; i--) 
	{
		this->site_list[i] = this->site_list[i - 1];
		this->site_list[i]->modify_index(i);
	}
	this->site_list[insert_index] = new_site;
};

void Voronori::generate_voronori()
{
	for (Vertice* vertice : this->vertice_list) {
		delete vertice;
	}
	for (Edge* edge : this->edge_list) {
		delete edge;
	}

	this->vertice_list.clear();
	this->edge_list.clear();
	this->clear_tree();
	this->root = nullptr;
	this->voronori_area_list.clear();
	this->event_queue = std::priority_queue<Event*>();
	for (Site* site : this->site_list)
	{
		Point_event* p_event = new Point_event(site);
		Voronori_area* v_area = new Voronori_area(site);
		this->event_queue.push(p_event);
		this->voronori_area_list.push_back(v_area);
	}
	while (!this->event_queue.empty())
	{
		Event* event = this->event_queue.top();
		this->event_queue.pop();
		if (event->get_type() == POINT_EVENT) 
		{
			this->handle_point_event((Point_event*)event);
		}
		else
		{
			this->handle_circle_event((Circle_event*)event);
		}
	}
};

void Voronori::handle_point_event(Point_event* p_event)
{
	if (this->root == nullptr)
	{
		this->root = new Voronori_node(p_event->get_site(), p_event->get_site(), nullptr);
	}
	else
	{
		this->search_and_insert(p_event->get_site());
	}
};

void Voronori::handle_circle_event(Circle_event* c_event)
{
	if(!c_event->is_able())
	{
		return;
	}
	Voronori_node* node = c_event->get_node();
	Voronori_node* pre = node->get_pre();
	Voronori_node* next = node->get_next();
	if (pre == nullptr || next == nullptr)
	{
		throw std::exception("The circle event has no pre node or next node");
	}

	if (pre != nullptr)
	{
		Circle_event* pre_event = (Circle_event*)pre->get_event();
		if (pre_event != nullptr)
		{
			pre_event->disable();
		}
		pre->set_next(next);
	}
	if (next != nullptr)
	{
		Circle_event* next_event = (Circle_event*)next->get_event();
		if (next_event != nullptr)
		{
			next_event->disable();
		}
		next->set_pre(pre);
	}

	Voronori_node* common_ancestor = seek_for_common_ancestor(pre, next);
	if (common_ancestor == nullptr)
	{
		throw std::exception("No common ancestor!");
	}
	common_ancestor->set_left_site(pre->get_left_site());
	common_ancestor->set_right_site(next->get_right_site());

	Point center = c_event->get_center();
	Vertice* vertice = new Vertice(center.get_x(), center.get_y(), std::vector<Edge*>(), this->vertice_list.size(), false);
	this->vertice_list.push_back(vertice);
	
	Site** sites = c_event->get_sites();
	Site* central = c_event->get_central_site();
	int cur_index = 0;
	Site** next_edge = new Site * [2];

	for (int i = 0; i < 3; i++)
	{
		if (sites[i] != central)
		{
			Edge* edge = this->voronori_area_list[central->get_index()]->seek_for_edge(sites[i]);
			edge->set_vertice(vertice);
			vertice->add_edge(edge);
			next_edge[cur_index++] = sites[i];
		}
	}

	Voronori_area* area_1 = this->voronori_area_list[next_edge[0]->get_index()];
	Voronori_area* area_2 = this->voronori_area_list[next_edge[1]->get_index()];
	Edge* edge = new Edge(area_1, area_2, this->edge_list.size());
	this->edge_list.push_back(edge);

	Voronori_node* parent = node->get_parent();
	Voronori_node* grandparent = parent->get_parent();
	Voronori_node* remain = parent->get_right_child();
	if (remain == node) 
	{
		remain = parent->get_left_child();
	}

	if (parent = grandparent->get_left_child()) 
	{
		grandparent->set_left_child(remain);
	}
	else
	{
		grandparent->set_right_child(remain);
	}
	remain->set_parent(grandparent);
	
	Voronori_node* pre_of_pre = pre->get_pre();
	Voronori_node* next_of_next = next->get_next();
	if (pre_of_pre != nullptr)
	{
		if (!(*(pre_of_pre->get_left_site()) == *(next->get_left_site())))
		{
			Event* event = new Circle_event(pre_of_pre->get_left_site(), pre->get_left_site(), next->get_left_site(), pre);
			pre->set_event(event);
			this->event_queue.push(event);
		}
	}
	if (next_of_next != nullptr)
	{
		if (!(*(next_of_next->get_left_site()) == *(pre->get_left_site())))
		{
			Event* event = new Circle_event(next_of_next->get_left_site(), pre->get_left_site(), next->get_left_site(), next);
			next->set_event(event);
			this->event_queue.push(event);                                                                                        
		}
	}
};

Voronori_node* Voronori::seek_for_common_ancestor(Voronori_node* pre, Voronori_node* next)
{
	Voronori_node* parent = pre->get_parent();
	std::map<Voronori_node*, bool> seek_map = std::map<Voronori_node*, bool>();
	
	while (parent != nullptr)
	{
		seek_map.insert(std::make_pair(parent, true));
		parent = parent->get_parent();
	}

	Voronori_node* target = next->get_parent();
	while (seek_map.find(target) == seek_map.end())
	{
		target = target->get_parent();
	}
	return target;
}

void recursive_clear_tree(Voronori_node* root)
{
	if (root == nullptr)
		return;
	recursive_clear_tree(root->get_left_child());
	recursive_clear_tree(root->get_right_child());
	delete root;
}

void Voronori::clear_tree()
{
	recursive_clear_tree(this->root);
}

std::vector<Vertice*> Voronori::get_vertice_list() const
{
	return this->vertice_list;
};

std::vector<Edge*> Voronori::get_edge_list() const
{
	return this->edge_list;
};

std::vector<Site*> Voronori::get_site_list() const
{
	return this->site_list;
};

std::vector<Boundary*> Voronori::get_boundary_list() const
{
	return this->boundary_list;
};

bool Voronori::all_covered() const
{
	return true;
};

void Voronori::search_and_insert(Site* site)
{
	Voronori_node* cur = this->root;
	while (!cur->is_leaf())
	{
		if (cur->smaller(site->get_x(), site->get_y()))
		{
			cur = cur->get_right_child();
		}
		else 
		{
			cur = cur->get_left_child();
		}
	}
	Site* arc_site = cur->get_left_site();
	Voronori_node* parent = cur->get_parent();
	Voronori_node* left = new Voronori_node(arc_site, site, nullptr);
	Voronori_node* right = new Voronori_node(site, arc_site, nullptr);

	if (cur->get_event() != nullptr)
	{
		Circle_event* event = (Circle_event*)cur->get_event();
		event->disable();
	}

	Voronori_node* left_of_left = new Voronori_node(arc_site, arc_site, nullptr);
	Voronori_node* right_of_right = new Voronori_node(arc_site, arc_site, nullptr);
	Voronori_node* new_arc = new Voronori_node(site, site, nullptr);
	new_arc->set_pre(left_of_left);
	new_arc->set_next(right_of_right);

	left_of_left->set_pre(cur->get_pre());
	left_of_left->set_next(new_arc);

	right_of_right->set_pre(new_arc);
	right_of_right->set_next(cur->get_next());

	if (cur->get_pre() != nullptr) 
	{
		cur->get_pre()->set_next(left_of_left);
	}
	if (cur->get_next() != nullptr)
	{
		cur->get_next()->set_pre(right_of_right);
	}

	Voronori_node* left_of_right; 
	Voronori_node* right_of_left;

	if (parent == nullptr)
	{
		parent = left;
		this->root = parent;
		right_of_left = right;
		left_of_right = new_arc ;
	}
	else if (parent->get_left_child() == cur)
	{
		parent->set_left_child(right);
		left_of_right = left;
		right_of_left = new_arc;
	}
	else
	{
		parent->set_right_child(left);
		right_of_left = right;
		left_of_right = new_arc;
	}
	right->set_left_child(left_of_right);
	right->set_right_child(right_of_right);
	left->set_left_child(left_of_left);
	left->set_right_child(right_of_left);

	Voronori_area* site_area = this->voronori_area_list[site->get_index()];
	Voronori_area* arc_site_area = this->voronori_area_list[arc_site->get_index()];
	Edge* edge = new Edge(site_area, arc_site_area, this->edge_list.size());
	left->set_edge(edge);
	right->set_edge(edge);
	site_area->add_edge(edge);
	arc_site_area->add_edge(edge);
	this->edge_list.push_back(edge);

	Voronori_node* left_neighbor = left_of_left;
	Voronori_node* left_left_neighbor = left_of_left->get_pre();
	if (left_neighbor != nullptr && left_left_neighbor != nullptr)
	{
		if (!(*(left_left_neighbor->get_left_site()) == *(new_arc->get_left_site())))
		{
			Event* circle_event = new Circle_event(left_left_neighbor->get_left_site(), 
				left_neighbor->get_left_site(), new_arc->get_left_site(), left_neighbor);
			left_neighbor->set_event(circle_event);
			this->event_queue.push(circle_event);
		}
	}

	Voronori_node* right_neighbor = right_of_right;
	Voronori_node* right_right_neighbor = right_of_right->get_next();
	if (right_neighbor != nullptr && right_right_neighbor != nullptr)
	{
		if (!(*(right_right_neighbor->get_right_site()) == *(new_arc->get_right_site())))
		{
			Event* circle_event = new Circle_event(right_right_neighbor->get_right_site(),
				right_neighbor->get_right_site(), new_arc->get_right_site(), right_neighbor);
			right_neighbor->set_event(circle_event);
			this->event_queue.push(circle_event);
		}
	}
}


