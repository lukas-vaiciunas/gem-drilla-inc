#include "DeathGameState.h"
#include "Game.h"
#include "Particle.h"
#include "Constants.h"
#include "Config.h"
#include "TextureData.h"
#include "SoundData.h"
#include "EventQueue.h"
#include "Event.h"
#include <SFML/Graphics/RenderTarget.hpp>

DeathGameState::DeathGameState(Game &game) :
	GameState(game),
	endTimer_(2.0f)
{
	game_.particlePool_.spawnDeathEffect(
		game_.player_.getX() + Constants::tileSize * 0.5f,
		game_.player_.getY() + Constants::tileSize * 0.5f,
		game.textureData_);

	SoundData::getInstance().playSound(3);
}

void DeathGameState::update(float deltaTime)
{
	game_.particlePool_.update(deltaTime);

	endTimer_.update(deltaTime);
	if (endTimer_.isDone())
	{
		EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::Results));
	}
}

void DeathGameState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::RenderStates worldStates = states;
	worldStates.transform.scale(Config::globalScale, Config::globalScale);
	worldStates.transform.translate(-game_.camera_.getX(), -game_.camera_.getY());

	sf::RenderStates uiStates = states;
	uiStates.transform.scale(Config::globalScale, Config::globalScale);

	target.draw(game_.map_, worldStates);
	target.draw(game_.particlePool_, worldStates);

	target.draw(game_.fuelGauge_, uiStates);
	target.draw(game_.depthGauge_, uiStates);
	target.draw(game_.profitGauge_, uiStates);
}