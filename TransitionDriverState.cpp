#include "TransitionDriverState.h"
#include "Menu.h"
#include "Upgrades.h"
#include "Game.h"
#include "Results.h"
#include "GameData.h"
#include "Config.h"
#include "EventQueue.h"
#include "Event.h"
#include <SFML/Graphics/RenderTarget.hpp>

TransitionDriverState::TransitionDriverState(
	DriverState *beginState,
	DriverStateType endStateType,
	GameData &gameData,
	const TextureData &textureData)
	:
	DriverState(DriverStateType::Transition),
	textureData_(textureData),
	gameData_(gameData),
	transitionState_(TransitionState::FadeIn),
	state_(beginState),
	endStateType_(endStateType),
	overlay_(),
	alpha_(0.0f),
	velAlpha_(512.0f)
{
	overlay_.setPosition(0.0f, 0.0f);
	overlay_.setSize(sf::Vector2f(Config::windowWidth, Config::windowHeight));
	overlay_.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha_)));

	if (beginState == nullptr)
	{
		this->advanceState_();

		transitionState_ = TransitionState::Done;
		EventQueue::getInstance().send(new EventChangeDriverStateExplicit(state_));
	}
}

TransitionDriverState::~TransitionDriverState()
{
	if (transitionState_ != TransitionState::Done)
	{
		delete state_;
	}
}

void TransitionDriverState::update(float deltaTime)
{
	state_->update(deltaTime);
	
	if (transitionState_ == TransitionState::FadeIn)
	{
		alpha_ += velAlpha_ * deltaTime;
		if (alpha_ >= 255)
		{
			alpha_ = 255;
			transitionState_ = TransitionState::FadeOut;
			this->advanceState_();
		}
	}
	else if (transitionState_ == TransitionState::FadeOut)
	{
		alpha_ -= velAlpha_ * deltaTime;
		if (alpha_ <= 0)
		{
			alpha_ = 0;
			transitionState_ = TransitionState::Done;
			EventQueue::getInstance().send(new EventChangeDriverStateExplicit(state_));
		}
	}

	overlay_.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha_)));
}

void TransitionDriverState::updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button)
{
	state_->updateOnMousePress(mouseX, mouseY, button);
}

void TransitionDriverState::updateOnMouseMove(int mouseX, int mouseY)
{
	state_->updateOnMouseMove(mouseX, mouseY);
}

void TransitionDriverState::updateOnKeyPress(sf::Keyboard::Key key)
{
	state_->updateOnKeyPress(key);
}

void TransitionDriverState::updateOnKeyRelease(sf::Keyboard::Key key)
{
	state_->updateOnKeyRelease(key);
}

void TransitionDriverState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*state_, states);
	target.draw(overlay_, states);
}

void TransitionDriverState::advanceState_()
{
	delete state_;

	switch (endStateType_)
	{
		case DriverStateType::Menu:
			state_ = new Menu(gameData_.getTotalMoney(), gameData_.getMaxDepth(), textureData_);
			gameData_.save();
			break;
		case DriverStateType::Upgrades:
			state_ = new Upgrades(
				gameData_.getTotalMoneyRef(),
				gameData_.getFuelUpgradeRef(),
				gameData_.getDrillUpgradeRef(),
				gameData_.getSpeedUpgradeRef(),
				textureData_);
			break;
		case DriverStateType::Game:
			state_ = new Game(
				3 + gameData_.getFuelUpgrade().getLevel(),
				50.0f + 50.0f * gameData_.getDrillUpgrade().getLevel(),
				32.0f + 8.0f * gameData_.getSpeedUpgrade().getLevel(),
				textureData_);
			break;
		case DriverStateType::Results:
			state_ = new Results(gameData_.getLastProfit(), gameData_.getLastMaxDepth(), textureData_);
			break;
	}
}