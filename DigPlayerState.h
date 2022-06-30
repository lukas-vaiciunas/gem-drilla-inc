#pragma once

#include "PlayerState.h"
#include "Direction.h"

class DigPlayerState : public PlayerState
{
public:
	DigPlayerState(Player &player, Direction direction);

	void update(float deltaTime) override;
private:
	bool *movementCondition_;
	int targetCol_;
	int targetRow_;
};