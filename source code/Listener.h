#pragma once

class Event;

#include "EventType.h"
#include <unordered_set>

class Listener
{
public:
	Listener(const std::unordered_set<EventType> &listenedEventTypes);
	virtual ~Listener();

	virtual void onEvent(const Event &ev) = 0;

	bool listensForEventType(EventType type) const;
private:
	std::unordered_set<EventType> listenedEventTypes_;
};