#include "Player.h"
#include "WaitPlayerState.h"
#include "TextureData.h"
#include "Map.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

Player::Player(int mapCol, int mapRow, float dps, float speed, const sf::Texture &texture, Map &map) :
	sf::Drawable(),
	map_(map),
	state_(new WaitPlayerState(*this)),
	sprite_(
		static_cast<float>(mapCol * Constants::tileSize),
		static_cast<float>(mapRow * Constants::tileSize),
		0.1f,
		Direction::Down,
		texture),
	mapCol_(mapCol),
	mapRow_(mapRow),
	isMovingUp_(false),
	isMovingDown_(false),
	isMovingLeft_(false),
	isMovingRight_(false),
	dps_(dps),
	speed_(speed)
{}

Player::~Player()
{
	delete state_;
}

void Player::update(float deltaTime)
{
	state_->update(deltaTime);
}

void Player::updateOnKeyPress(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Key::W:
			isMovingUp_ = true;
			break;
		case sf::Keyboard::Key::A:
			isMovingLeft_ = true;
			break;
		case sf::Keyboard::Key::S:
			isMovingDown_ = true;
			break;
		case sf::Keyboard::Key::D:
			isMovingRight_ = true;
			break;
	}
}

void Player::updateOnKeyRelease(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Key::W:
			isMovingUp_ = false;
			break;
		case sf::Keyboard::Key::A:
			isMovingLeft_ = false;
			break;
		case sf::Keyboard::Key::S:
			isMovingDown_ = false;
			break;
		case sf::Keyboard::Key::D:
			isMovingRight_ = false;
			break;
	}
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

int Player::getMapCol() const
{
	return mapCol_;
}

int Player::getMapRow() const
{
	return mapRow_;
}

float Player::getX() const
{
	return sprite_.getPosition().x;
}

float Player::getY() const
{
	return sprite_.getPosition().y;
}

Direction Player::verifyMovement_()
{
	if (isMovingUp_
		&& map_.isInBounds(mapCol_, mapRow_ - 1)
		&& !map_.existsMinableTile(mapCol_, mapRow_ - 1))
	{
		return Direction::Up;
	}
	else if (isMovingDown_
		&& map_.isInBounds(mapCol_, mapRow_ + 1)
		&& !map_.existsMinableTile(mapCol_, mapRow_ + 1))
	{
		return Direction::Down;
	}
	else if (isMovingLeft_
		&& map_.isInBounds(mapCol_ - 1, mapRow_)
		&& !map_.existsMinableTile(mapCol_ - 1, mapRow_))
	{
		return Direction::Left;
	}
	else if (isMovingRight_
		&& map_.isInBounds(mapCol_ + 1, mapRow_)
		&& !map_.existsMinableTile(mapCol_ + 1, mapRow_))
	{
		return Direction::Right;
	}
	else return Direction::None;
}

Direction Player::verifyDigging_()
{
	if (isMovingUp_
		&& map_.isInBounds(mapCol_, mapRow_ - 1)
		&& map_.existsMinableTile(mapCol_, mapRow_ - 1))
	{
		return Direction::Up;
	}
	else if (isMovingDown_
		&& map_.isInBounds(mapCol_, mapRow_ + 1)
		&& map_.existsMinableTile(mapCol_, mapRow_ + 1))
	{
		return Direction::Down;
	}
	else if (isMovingLeft_
		&& map_.isInBounds(mapCol_ - 1, mapRow_)
		&& map_.existsMinableTile(mapCol_ - 1, mapRow_))
	{
		return Direction::Left;
	}
	else if (isMovingRight_
		&& map_.isInBounds(mapCol_ + 1, mapRow_)
		&& map_.existsMinableTile(mapCol_ + 1, mapRow_))
	{
		return Direction::Right;
	}
	else return Direction::None;
}

void Player::changeState_(PlayerState *state)
{
	delete state_;

	state_ = state;
}