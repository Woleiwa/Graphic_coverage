#include "site.h"

bool Site::operator<(const Site& another) const 
{
	if (this->y < another.y) {
		return true;
	}
	else if (this->y == another.y) {
		if (this->x < another.y) {
			return true;
		}
	}

	return false;
}

bool Site::operator==(const Site& another) const
{
	return (this->x == another.x) && (this->y == another.y);
}

int Site::get_index() const {
	return this->index;
}

void Site::modify_index(int index) {
	this->index = index;
}

