#include "EventQueue.h"
#include "Event.h"
#include "Listener.h"

EventQueue::EventQueue() :
	queue_(),
	listeners_()
{}

EventQueue::~EventQueue()
{
	while (!queue_.empty())
	{
		delete queue_.front();
		queue_.pop();
	}
}

EventQueue &EventQueue::getInstance()
{
	static EventQueue instance;
	return instance;
}

void EventQueue::dispatch()
{
	while (!queue_.empty())
	{
		const Event &ev = *queue_.front();

		for (auto it = listeners_.cbegin(); it != listeners_.cend(); ++it)
		{
			if ((*it)->listensForEventType(ev.getType()))
			{
				(*it)->onEvent(ev);
			}
		}

		delete queue_.front();
		queue_.pop();
	}
}

void EventQueue::send(Event *ev)
{
	queue_.push(ev);
}

void EventQueue::attachListener(Listener *listener)
{
	listeners_.emplace(listener);
}

void EventQueue::detachListener(Listener *listener)
{
	auto it = listeners_.find(listener);

	if (it != listeners_.cend())
	{
		listeners_.erase(it);
	}
}