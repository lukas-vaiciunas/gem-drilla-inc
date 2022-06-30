#pragma once

#include "Timer.h"
#include "Direction.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class PlayerSprite : public sf::Drawable
{
public:
	PlayerSprite(float x, float y, float frameSecs, Direction direction, const sf::Texture &texture);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setDirection(Direction direction);
	void setPosition(float x, float y);
	void move(float dX, float dY);

	const sf::Vector2f &getPosition() const;
private:
	sf::Sprite sprite_;
	Timer frameTimer_;
	Direction direction_;

	uint8_t numFrames_;
	uint8_t frameIndex_;
};