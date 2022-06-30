#include "Listener.h"
#include "EventQueue.h"

Listener::Listener(const std::unordered_set<EventType> &listenedEventTypes) :
	listenedEventTypes_(listenedEventTypes)
{
	EventQueue::getInstance().attachListener(this);
}

Listener::~Listener()
{
	EventQueue::getInstance().detachListener(this);
}

bool Listener::listensForEventType(EventType type) const
{
	return listenedEventTypes_.find(type) != listenedEventTypes_.cend();
}