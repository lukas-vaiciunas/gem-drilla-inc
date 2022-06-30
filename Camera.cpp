#include "Camera.h"
#include "Config.h"

Camera::Camera(float x, float y) :
	x_(x),
	y_(y)
{}

void Camera::centerOn(float x, float y, float minX, float maxX, float maxY)
{
	float scaleFactor = 1.0f / Config::globalScale;
	float viewWidth = Config::windowWidth * scaleFactor;
	float viewHeight = Config::windowHeight * scaleFactor;

	x_ = x - Config::windowWidth * 0.5f * scaleFactor;
	y_ = y - Config::windowHeight * 0.5f * scaleFactor;

	if (x_ < minX) x_ = minX;
	if (x_ > maxX - viewWidth) x_ = maxX - viewWidth;
	if (y_ > maxY - viewHeight) y_ = maxY - viewHeight;
}

float Camera::getX() const
{
	return x_;
}

float Camera::getY() const
{
	return y_;
}