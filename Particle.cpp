#include "Particle.h"
#include <SFML/Graphics/RenderTarget.hpp>

Particle::Particle(
	float x, float y,
	float velX, float velY, float velAngle,
	float accX, float accY,
	float durationSecs,
	const sf::Texture &texture)
	:
	sprite_(texture),
	durationTimer_(durationSecs),
	x_(x),
	y_(y),
	angle_(0.0f),
	velX_(velX),
	velY_(velY),
	velAngle_(velAngle),
	accX_(accX),
	accY_(accY)
{
	sprite_.setOrigin(sprite_.getLocalBounds().width * 0.5f, sprite_.getLocalBounds().height * 0.5f);
	sprite_.setPosition(x, y);
}

void Particle::update(float deltaTime)
{
	durationTimer_.update(deltaTime);

	x_ += velX_ * deltaTime;
	y_ += velY_ * deltaTime;
	velX_ += accX_ * deltaTime;
	velY_ += accY_ * deltaTime;
	angle_ += velAngle_ * deltaTime;

	sprite_.setPosition(x_, y_);
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	float scale = (durationTimer_.getTargetSecs() - durationTimer_.getElapsedSecs()) / durationTimer_.getTargetSecs();

	states.transform.scale(scale, scale, x_ + 0.5f, y_ + 0.5f);
	states.transform.rotate(angle_, x_ + 0.5f, y_ + 0.5f);

	target.draw(sprite_, states);
}

bool Particle::isDead() const
{
	return durationTimer_.isDone();
}