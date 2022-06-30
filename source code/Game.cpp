#include "Game.h"
#include "PlayGameState.h"
#include "DeathGameState.h"
#include "TextureData.h"
#include "EventQueue.h"
#include "SoundData.h"
#include "Event.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

Game::Game(uint8_t numFuel, float drillDPS, float playerSpeed, const TextureData &textureData) :
	DriverState(DriverStateType::Game),
	Listener({ EventType::PlayerMoved, EventType::BlockMined }),
	textureData_(textureData),
	state_(nullptr),
	stateType_(GameStateType::None),
	particlePool_(100),
	map_(30, 120, textureData, particlePool_),
	player_(15, 0, drillDPS, playerSpeed, textureData.getTexture(1), map_),
	camera_(0.0f, 0.0f),
	fuelGauge_(numFuel, 5.0f, textureData.getTexture(203), textureData.getTexture(201), textureData.getTexture(202)),
	depthGauge_(textureData.getTexture(204)),
	profitGauge_(textureData.getTexture(205))
{
	camera_.centerOn(player_.getX() + 4.0f, player_.getY() + 4.0f, 0.0f, map_.getWidth(), map_.getHeight());
	map_.forceUpdateVisibility(player_.getMapCol(), player_.getMapRow());

	this->changeState_(GameStateType::Play);

	SoundData::getInstance().playMusic(2);
}

Game::~Game()
{
	this->changeState_(GameStateType::None);
}

void Game::onEvent(const Event &ev)
{
	if (ev.getType() == EventType::PlayerMoved)
	{
		map_.updateVisibility(player_.getMapCol(), player_.getMapRow());
		depthGauge_.setDepth(player_.getMapRow());
	}
	else if (ev.getType() == EventType::BlockMined)
	{
		const EventBlockMined &trueEv = static_cast<const EventBlockMined &>(ev);

		profitGauge_.addProfit(trueEv.getValue());
	}
}

void Game::update(float deltaTime)
{
	state_->update(deltaTime);
}

void Game::updateOnKeyPress(sf::Keyboard::Key key)
{
	state_->updateOnKeyPress(key);
}

void Game::updateOnKeyRelease(sf::Keyboard::Key key)
{
	state_->updateOnKeyRelease(key);
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*state_, states);
}

void Game::changeState_(GameStateType toStateType)
{
	if (stateType_ != GameStateType::None)
	{
		delete state_;
	}

	stateType_ = toStateType;

	switch (stateType_)
	{
		case GameStateType::Play:
			state_ = new PlayGameState(*this);
			break;
		case GameStateType::Death:
			state_ = new DeathGameState(*this);
			break;
	}
}