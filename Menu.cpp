#include "Menu.h"
#include "TextureData.h"
#include "EventQueue.h"
#include "Event.h"
#include "FontData.h"
#include "SoundData.h"
#include "Config.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

Menu::Menu(uint64_t totalMoney, uint8_t maxDepth, const TextureData &textureData) :
	DriverState(DriverStateType::Menu),
	backdrop_(textureData),
	playButton_(
		Config::windowWidth * 0.25f / Config::globalScale - 8.0f,
		Config::windowHeight * 0.8f / Config::globalScale - 8.0f,
		textureData.getTexture(301)),
	upgradeButton_(
		Config::windowWidth * 0.5f / Config::globalScale - 8.0f,
		Config::windowHeight * 0.8f / Config::globalScale - 8.0f,
		textureData.getTexture(302)),
	quitButton_(
		Config::windowWidth * 0.75f / Config::globalScale - 8.0f,
		Config::windowHeight * 0.8f / Config::globalScale - 8.0f,
		textureData.getTexture(303)),
	totalMoneySprite_(textureData.getTexture(207)),
	maxDepthSprite_(textureData.getTexture(206)),
	totalMoneyText_(),
	maxDepthText_(),
	gemText_(),
	drillaText_(),
	incText_(),
	copyrightText_()
{
	totalMoneySprite_.setPosition(1.0f, 1.0f);
	maxDepthSprite_.setPosition(1.0f, 10.0f);

	totalMoneyText_.setFont(FontData::getInstance().getFont());
	totalMoneyText_.setCharacterSize(Config::mediumFontSize);
	totalMoneyText_.setFillColor(sf::Color(236, 236, 236));
	totalMoneyText_.setOutlineColor(sf::Color(0, 0, 0));
	totalMoneyText_.setOutlineThickness(Config::globalScale);
	totalMoneyText_.setString(std::to_string(totalMoney));
	totalMoneyText_.setOrigin(
		totalMoneyText_.getLocalBounds().left,
		totalMoneyText_.getLocalBounds().top + totalMoneyText_.getLocalBounds().height * 0.5f);
	totalMoneyText_.setPosition(11.0f * Config::globalScale, 5.0f * Config::globalScale);

	maxDepthText_.setFont(FontData::getInstance().getFont());
	maxDepthText_.setCharacterSize(Config::mediumFontSize);
	maxDepthText_.setFillColor(sf::Color(236, 236, 236));
	maxDepthText_.setOutlineColor(sf::Color(0, 0, 0));
	maxDepthText_.setOutlineThickness(Config::globalScale);
	maxDepthText_.setString(std::to_string(maxDepth));
	maxDepthText_.setOrigin(
		maxDepthText_.getLocalBounds().left,
		maxDepthText_.getLocalBounds().top + maxDepthText_.getLocalBounds().height * 0.5f);
	maxDepthText_.setPosition(11.0f * Config::globalScale, 14.0f * Config::globalScale);

	gemText_.setFont(FontData::getInstance().getFont());
	gemText_.setCharacterSize(Config::largeFontSize);
	gemText_.setFillColor(sf::Color(192, 88, 88));
	gemText_.setOutlineColor(sf::Color(0, 0, 0));
	gemText_.setOutlineThickness(Config::globalScale);
	gemText_.setString("GEM");
	gemText_.setOrigin(
		gemText_.getLocalBounds().left + gemText_.getLocalBounds().width * 0.5f,
		gemText_.getLocalBounds().top + gemText_.getLocalBounds().height * 0.5f);
	gemText_.setPosition(Config::windowWidth * 0.45f, Config::windowHeight * 0.2f);

	drillaText_.setFont(FontData::getInstance().getFont());
	drillaText_.setCharacterSize(Config::largeFontSize);
	drillaText_.setFillColor(sf::Color(116, 180, 116));
	drillaText_.setOutlineColor(sf::Color(0, 0, 0));
	drillaText_.setOutlineThickness(Config::globalScale);
	drillaText_.setString("DRILLA");
	drillaText_.setOrigin(
		drillaText_.getLocalBounds().left + drillaText_.getLocalBounds().width * 0.5f,
		drillaText_.getLocalBounds().top + drillaText_.getLocalBounds().height * 0.5f);
	drillaText_.setPosition(Config::windowWidth * 0.5f, Config::windowHeight * 0.2f + gemText_.getLocalBounds().height * 1.1f);

	incText_.setFont(FontData::getInstance().getFont());
	incText_.setCharacterSize(Config::largeFontSize);
	incText_.setFillColor(sf::Color(124, 180, 212));
	incText_.setOutlineColor(sf::Color(0, 0, 0));
	incText_.setOutlineThickness(Config::globalScale);
	incText_.setString("INC.");
	incText_.setOrigin(
		incText_.getLocalBounds().left + incText_.getLocalBounds().width * 0.5f,
		incText_.getLocalBounds().top + incText_.getLocalBounds().height * 0.5f);
	incText_.setPosition(Config::windowWidth * 0.55f, Config::windowHeight * 0.2f + (gemText_.getLocalBounds().height + drillaText_.getLocalBounds().height) * 1.1f);

	copyrightText_.setFont(FontData::getInstance().getFont());
	copyrightText_.setCharacterSize(Config::smallFontSize);
	copyrightText_.setFillColor(sf::Color(236, 236, 236));
	copyrightText_.setOutlineColor(sf::Color(0, 0, 0));
	copyrightText_.setOutlineThickness(Config::globalScale);
	copyrightText_.setString("(C) 2022 Lukas Vaiciunas");
	copyrightText_.setPosition(Config::globalScale, Config::windowHeight - Config::smallFontSize - Config::globalScale);

	SoundData::getInstance().playMusic(1);
}

void Menu::update(float deltaTime)
{
	playButton_.update(deltaTime);
	upgradeButton_.update(deltaTime);
	quitButton_.update(deltaTime);
}

void Menu::updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button)
{
	if (playButton_.isPressed(mouseX, mouseY, button))
	{
		SoundData::getInstance().playSound(5);
		EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::Game));
	}
	else if (upgradeButton_.isPressed(mouseX, mouseY, button))
	{
		SoundData::getInstance().playSound(5);
		EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::Upgrades));
	}
	else if (quitButton_.isPressed(mouseX, mouseY, button))
	{
		SoundData::getInstance().playSound(5);
		EventQueue::getInstance().send(new EventQuit());
	}
}

void Menu::updateOnMouseMove(int mouseX, int mouseY)
{
	playButton_.updateOnMouseMove(mouseX, mouseY);
	upgradeButton_.updateOnMouseMove(mouseX, mouseY);
	quitButton_.updateOnMouseMove(mouseX, mouseY);
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::globalScale, Config::globalScale);

	target.draw(backdrop_, states);

	target.draw(totalMoneySprite_, states);
	target.draw(maxDepthSprite_, states);

	target.draw(totalMoneyText_);
	target.draw(maxDepthText_);

	target.draw(gemText_);
	target.draw(drillaText_);
	target.draw(incText_);

	target.draw(copyrightText_);

	target.draw(playButton_, states);
	target.draw(upgradeButton_, states);
	target.draw(quitButton_, states);
}