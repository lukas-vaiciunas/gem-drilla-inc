#pragma once

class DriverState;

#include "EventType.h"
#include "DriverStateType.h"

class Event
{
public:
	Event(EventType type) :
		type_(type)
	{}

	virtual ~Event() {}

	EventType getType() const
	{
		return type_;
	}
private:
	EventType type_;
};

class EventChangeDriverState : public Event
{
public:
	EventChangeDriverState(DriverStateType stateType) :
		Event(EventType::ChangeDriverState),
		stateType_(stateType)
	{}

	DriverStateType getStateType() const
	{
		return stateType_;
	}
private:
	DriverStateType stateType_;
};

class EventChangeDriverStateExplicit : public Event
{
public:
	EventChangeDriverStateExplicit(DriverState *state) :
		Event(EventType::ChangeDriverStateExplicit),
		state_(state)
	{}

	DriverState *getState() const
	{
		return state_;
	}
private:
	DriverState *state_;
};

class EventQuit : public Event
{
public:
	EventQuit() :
		Event(EventType::Quit)
	{}
};

class EventPlayerMoved : public Event
{
public:
	EventPlayerMoved() :
		Event(EventType::PlayerMoved)
	{}
};

class EventBlockMined : public Event
{
public:
	EventBlockMined(uint64_t value) :
		Event(EventType::BlockMined),
		value_(value)
	{}

	uint64_t getValue() const
	{
		return value_;
	}
private:
	uint64_t value_;
};

class EventGameOver : public Event
{
public:
	EventGameOver(uint64_t profit, uint8_t maxDepth) :
		Event(EventType::GameOver),
		profit_(profit),
		maxDepth_(maxDepth)
	{}

	uint64_t getProfit() const
	{
		return profit_;
	}

	uint8_t getMaxDepth() const
	{
		return maxDepth_;
	}
private:
	uint64_t profit_;
	uint8_t maxDepth_;
};