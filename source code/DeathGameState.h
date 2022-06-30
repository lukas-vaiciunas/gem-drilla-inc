#pragma once

#include "GameState.h"
#include "Timer.h"

class DeathGameState : public GameState
{
public:
	DeathGameState(Game &game);

	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	Timer endTimer_;
};