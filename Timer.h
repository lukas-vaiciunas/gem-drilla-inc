#pragma once

class Timer
{
public:
	Timer(float targetSecs);

	void update(float deltaTime);

	void reset();

	float getTargetSecs() const;
	float getElapsedSecs() const;
	bool isDone() const;
private:
	float targetSecs_;
	float elapsedSecs_;
};