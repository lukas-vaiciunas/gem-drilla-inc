#include "PlayGameState.h"
#include "Game.h"
#include "EventQueue.h"
#include "Event.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

PlayGameState::PlayGameState(Game &game) :
	GameState(game)
{}

void PlayGameState::update(float deltaTime)
{
	game_.player_.update(deltaTime);
	game_.particlePool_.update(deltaTime);

	game_.camera_.centerOn(game_.player_.getX() + 4.0f, game_.player_.getY() + 4.0f, 0.0f, game_.map_.getWidth(), game_.map_.getHeight());

	game_.fuelGauge_.update(deltaTime);
	if (game_.fuelGauge_.isEmpty())
	{
		EventQueue::getInstance().send(new EventGameOver(game_.profitGauge_.getProfit(), game_.depthGauge_.getMaxDepth()));
		//EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::Results));

		game_.changeState_(GameStateType::Death);
	}
}

void PlayGameState::updateOnKeyPress(sf::Keyboard::Key key)
{
	game_.player_.updateOnKeyPress(key);
}

void PlayGameState::updateOnKeyRelease(sf::Keyboard::Key key)
{
	game_.player_.updateOnKeyRelease(key);
}

void PlayGameState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::RenderStates worldStates = states;
	worldStates.transform.scale(Config::globalScale, Config::globalScale);
	worldStates.transform.translate(-game_.camera_.getX(), -game_.camera_.getY());

	sf::RenderStates uiStates = states;
	uiStates.transform.scale(Config::globalScale, Config::globalScale);

	target.draw(game_.map_, worldStates);
	target.draw(game_.player_, worldStates);
	target.draw(game_.particlePool_, worldStates);

	target.draw(game_.fuelGauge_, uiStates);
	target.draw(game_.depthGauge_, uiStates);
	target.draw(game_.profitGauge_, uiStates);
}