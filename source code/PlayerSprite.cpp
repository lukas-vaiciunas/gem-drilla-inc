#include "PlayerSprite.h"
#include <SFML/Graphics/RenderTarget.hpp>

PlayerSprite::PlayerSprite(float x, float y, float frameSecs, Direction direction, const sf::Texture &texture) :
	sf::Drawable(),
	sprite_(texture),
	frameTimer_(frameSecs),
	direction_(Direction::None),
	numFrames_(2),
	frameIndex_(0)
{
	sprite_.setPosition(x, y);

	this->setDirection(direction);
}

void PlayerSprite::update(float deltaTime)
{
	frameTimer_.update(deltaTime);

	if (frameTimer_.isDone())
	{
		frameTimer_.reset();

		frameIndex_ = (frameIndex_ + 1) % numFrames_;

		sprite_.setTextureRect(sf::IntRect(frameIndex_ * 8, sprite_.getTextureRect().top, 8, 8));
	}
}

void PlayerSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

void PlayerSprite::setDirection(Direction direction)
{
	direction_ = direction;

	int frameY = 0;

	switch (direction_)
	{
		case Direction::Up:
			frameY = 0;
			break;
		case Direction::Down:
			frameY = 8;
			break;
		case Direction::Left:
			frameY = 16;
			break;
		case Direction::Right:
			frameY = 24;
			break;
	}

	sprite_.setTextureRect(sf::IntRect(frameIndex_ * 8, frameY, 8, 8));
}

void PlayerSprite::setPosition(float x, float y)
{
	sprite_.setPosition(x, y);
}

void PlayerSprite::move(float dX, float dY)
{
	sprite_.move(dX, dY);
}

const sf::Vector2f &PlayerSprite::getPosition() const
{
	return sprite_.getPosition();
}