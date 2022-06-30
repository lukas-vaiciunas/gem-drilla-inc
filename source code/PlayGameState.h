#pragma once

#include "GameState.h"

class PlayGameState : public GameState
{
public:
	PlayGameState(Game &game);

	void update(float deltaTime) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};