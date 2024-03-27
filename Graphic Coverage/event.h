#pragma once
#ifndef _EVENT_H_
#define _EVENT_H_

#define POINT_EVENT true
#define CIRCLE_EVENT false
class Event
{
public:
	virtual double get_y() const;
	virtual bool get_type() const = 0;
	bool operator< (const Event& another) const;
};
#endif // !_EVENT_H_



