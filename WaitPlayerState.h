#pragma once

#include "PlayerState.h"

class WaitPlayerState : public PlayerState
{
public:
	WaitPlayerState(Player &player);

	void update(float deltaTime) override;
};