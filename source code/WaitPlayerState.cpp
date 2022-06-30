#include "WaitPlayerState.h"
#include "MovePlayerState.h"
#include "DigPlayerState.h"
#include "Player.h"

WaitPlayerState::WaitPlayerState(Player &player) :
	PlayerState(player)
{}

void WaitPlayerState::update(float deltaTime)
{
	Direction moveDirection = player_.verifyMovement_();

	if (moveDirection != Direction::None)
	{
		player_.changeState_(new MovePlayerState(player_, moveDirection));
	}
	else
	{
		Direction digDirection = player_.verifyDigging_();

		if (digDirection != Direction::None)
		{
			player_.changeState_(new DigPlayerState(player_, digDirection));
		}
	}
}