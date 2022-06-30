#include "Timer.h"

Timer::Timer(float targetSecs) :
	targetSecs_(targetSecs),
	elapsedSecs_(0.0f)
{}

void Timer::update(float deltaTime)
{
	elapsedSecs_ += deltaTime;
}

void Timer::reset()
{
	elapsedSecs_ = 0.0f;
}

float Timer::getTargetSecs() const
{
	return targetSecs_;
}

float Timer::getElapsedSecs() const
{
	return elapsedSecs_;
}

bool Timer::isDone() const
{
	return elapsedSecs_ >= targetSecs_;
}