#pragma once

class Player;

#include <SFML/Window/Keyboard.hpp>

class PlayerState
{
public:
	PlayerState(Player &player);
	virtual ~PlayerState() {}

	virtual void update(float deltaTime) {}
protected:
	Player &player_;
};