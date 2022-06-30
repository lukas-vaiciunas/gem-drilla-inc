#pragma once

class Game;

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Keyboard.hpp>

class GameState : public sf::Drawable
{
public:
	GameState(Game &game);
	virtual ~GameState() {}

	virtual void update(float deltaTime) {}
	virtual void updateOnKeyPress(sf::Keyboard::Key key) {}
	virtual void updateOnKeyRelease(sf::Keyboard::Key key) {}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {}
protected:
	Game &game_;
};