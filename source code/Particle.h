#pragma once

#include "Timer.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Particle : public sf::Drawable
{
public:
	Particle(
		float x, float y,
		float velX, float velY, float velAngle,
		float accX, float accY,
		float durationSecs,
		const sf::Texture &texture);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isDead() const;
private:
	sf::Sprite sprite_;
	Timer durationTimer_;
	float x_;
	float y_;
	float angle_;
	float velX_;
	float velY_;
	float velAngle_;
	float accX_;
	float accY_;
};