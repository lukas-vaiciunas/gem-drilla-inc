#include "MovePlayerState.h"
#include "WaitPlayerState.h"
#include "TextureData.h"
#include "Player.h"
#include "EventQueue.h"
#include "Event.h"
#include "Constants.h"

MovePlayerState::MovePlayerState(Player &player, Direction direction) :
	PlayerState(player),
	direction_(direction),
	targetMapCol_(-1),
	targetMapRow_(-1),
	targetX_(0.0f),
	targetY_(0.0f),
	velX_(0.0f),
	velY_(0.0f)
{
	this->updateDestination_();
}

void MovePlayerState::update(float deltaTime)
{
	player_.sprite_.update(deltaTime);

	player_.sprite_.move(velX_ * deltaTime, velY_ * deltaTime);
	
	if (reachedDestination_())
	{
		player_.sprite_.setPosition(targetX_, targetY_);
		player_.mapCol_ = targetMapCol_;
		player_.mapRow_ = targetMapRow_;

		EventQueue::getInstance().send(new EventPlayerMoved());

		this->reset_();
	}
}

void MovePlayerState::reset_()
{
	direction_ = player_.verifyMovement_();

	if (direction_ == Direction::None)
	{
		player_.changeState_(new WaitPlayerState(player_));
	}
	else
	{
		updateDestination_();
	}
}

void MovePlayerState::updateDestination_()
{
	direction_ = player_.verifyMovement_();

	switch (direction_)
	{
		case Direction::Up:
			targetMapCol_ = player_.mapCol_;
			targetMapRow_ = player_.mapRow_ - 1;
			velX_ = 0.0f;
			velY_ = -player_.speed_;
			break;
		case Direction::Down:
			targetMapCol_ = player_.mapCol_;
			targetMapRow_ = player_.mapRow_ + 1;
			velX_ = 0.0f;
			velY_ = player_.speed_;
			break;
		case Direction::Left:
			targetMapCol_ = player_.mapCol_ - 1;
			targetMapRow_ = player_.mapRow_;
			velX_ = -player_.speed_;
			velY_ = 0.0f;
			break;
		case Direction::Right:
			targetMapCol_ = player_.mapCol_ + 1;
			targetMapRow_ = player_.mapRow_;
			velX_ = player_.speed_;
			velY_ = 0.0f;
			break;
	}

	player_.sprite_.setDirection(direction_);

	targetX_ = static_cast<float>(targetMapCol_ * Constants::tileSize);
	targetY_ = static_cast<float>(targetMapRow_ * Constants::tileSize);
}

bool MovePlayerState::reachedDestination_() const
{
	switch (direction_)
	{
		case Direction::Up:
			return player_.sprite_.getPosition().y <= targetY_;
		case Direction::Down:
			return player_.sprite_.getPosition().y >= targetY_;
		case Direction::Left:
			return player_.sprite_.getPosition().x <= targetX_;
		case Direction::Right:
			return player_.sprite_.getPosition().x >= targetX_;
	}

	return false;
}