#include "DigPlayerState.h"
#include "Player.h"
#include "WaitPlayerState.h"
#include "TextureData.h"
#include "Map.h"

DigPlayerState::DigPlayerState(Player &player, Direction direction) :
	PlayerState(player),
	movementCondition_(nullptr),
	targetCol_(0),
	targetRow_(0)
{
	switch (direction)
	{
		case Direction::Up:
			movementCondition_ = &player_.isMovingUp_;
			targetCol_ = player_.mapCol_;
			targetRow_ = player_.mapRow_ - 1;
			break;
		case Direction::Down:
			movementCondition_ = &player_.isMovingDown_;
			targetCol_ = player_.mapCol_;
			targetRow_ = player_.mapRow_ + 1;
			break;
		case Direction::Left:
			movementCondition_ = &player_.isMovingLeft_;
			targetCol_ = player_.mapCol_ - 1;
			targetRow_ = player_.mapRow_;
			break;
		case Direction::Right:
			movementCondition_ = &player_.isMovingRight_;
			targetCol_ = player_.mapCol_ + 1;
			targetRow_ = player_.mapRow_;
			break;
	}

	player_.sprite_.setDirection(direction);
}

void DigPlayerState::update(float deltaTime)
{
	player_.sprite_.update(deltaTime);

	player_.map_.dig(targetCol_, targetRow_, player_.dps_ * deltaTime);

	if (!*movementCondition_ || !player_.map_.existsMinableTile(targetCol_, targetRow_))
	{
		player_.changeState_(new WaitPlayerState(player_));
	}
}