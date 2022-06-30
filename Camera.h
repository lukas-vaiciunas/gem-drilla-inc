#pragma once

class Camera
{
public:
	Camera(float x, float y);

	void centerOn(float x, float y, float minX, float maxX, float maxY);

	float getX() const;
	float getY() const;
private:
	float x_;
	float y_;
};