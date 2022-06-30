#pragma once

#include "PlayerState.h"
#include "Direction.h"

class MovePlayerState : public PlayerState
{
public:
	MovePlayerState(Player &player, Direction direction);

	void update(float deltaTime) override;
private:
	Direction direction_;
	int targetMapCol_;
	int targetMapRow_;
	float targetX_;
	float targetY_;
	float velX_;
	float velY_;

	void reset_();
	void updateDestination_();
	bool reachedDestination_() const;
};