#include "event.h"
double Event::get_y() const
{
	return 0;
}

bool Event::operator< (const Event& another) const
{
	return this->get_y() < another.get_y();
}