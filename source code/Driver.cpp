#include "Driver.h"
#include "Menu.h"
#include "Upgrades.h"
#include "Game.h"
#include "Results.h"
#include "TransitionDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <ShlObj.h>
#include <atlstr.h>

Driver::Driver() :
	DriverState(DriverStateType::None),
	Listener({ EventType::ChangeDriverState, EventType::ChangeDriverStateExplicit, EventType::Quit, EventType::GameOver }),
	state_(nullptr),
	stateType_(DriverStateType::None),
	textureData_("data/textures.txt"),
	gameData_(),
	isDone_(false)
{
	TCHAR szPath[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath);

	std::wstring savePath = std::wstring(szPath) + L"\\Lukas Vaiciunas\\Gem Drilla Inc\\";
	gameData_.init(savePath, L"save.bin");

	this->changeState_(DriverStateType::Menu);
}

Driver::~Driver()
{
	delete state_;
}

void Driver::onEvent(const Event &ev)
{
	if (ev.getType() == EventType::ChangeDriverState)
	{
		const EventChangeDriverState &trueEv = static_cast<const EventChangeDriverState &>(ev);

		this->changeState_(trueEv.getStateType());
	}
	else if (ev.getType() == EventType::ChangeDriverStateExplicit)
	{
		const EventChangeDriverStateExplicit &trueEv = static_cast<const EventChangeDriverStateExplicit &>(ev);

		this->changeState_(trueEv.getState());
	}
	else if (ev.getType() == EventType::Quit)
	{
		isDone_ = true;
	}
	else if (ev.getType() == EventType::GameOver)
	{
		const EventGameOver &trueEv = static_cast<const EventGameOver &>(ev);

		gameData_.setLastProfit(trueEv.getProfit());
		gameData_.setLastMaxDepth(trueEv.getMaxDepth());

		gameData_.addToTotalMoney(gameData_.getLastProfit());
		gameData_.setMaxDepth(std::max(gameData_.getMaxDepth(), gameData_.getLastMaxDepth()));
	}
}

void Driver::update(float deltaTime)
{
	state_->update(deltaTime);

	EventQueue::getInstance().dispatch();
}

void Driver::updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button)
{
	state_->updateOnMousePress(mouseX, mouseY, button);
}

void Driver::updateOnMouseMove(int mouseX, int mouseY)
{
	state_->updateOnMouseMove(mouseX, mouseY);
}

void Driver::updateOnKeyPress(sf::Keyboard::Key key)
{
	state_->updateOnKeyPress(key);
}

void Driver::updateOnKeyRelease(sf::Keyboard::Key key)
{
	state_->updateOnKeyRelease(key);
}

void Driver::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*state_, states);
}

bool Driver::isDone() const
{
	return isDone_;
}

void Driver::changeState_(DriverStateType toStateType)
{
	state_ = new TransitionDriverState(state_, toStateType, gameData_, textureData_);
	stateType_ = DriverStateType::Transition;
}

void Driver::changeState_(DriverState *toState)
{
	delete state_;

	state_ = toState;
	stateType_ = state_->getType();
}