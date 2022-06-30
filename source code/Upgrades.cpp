#include "Upgrades.h"
#include "TextureData.h"
#include "EventQueue.h"
#include "Event.h"
#include "FontData.h"
#include "SoundData.h"
#include "Config.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

Upgrades::Upgrades(
	uint64_t &totalMoney,
	Upgrade &fuelUpgrade,
	Upgrade &drillUpgrade,
	Upgrade &speedUpgrade,
	const TextureData &textureData)
	:
	DriverState(DriverStateType::Upgrades),
	totalMoney_(totalMoney),
	totalMoneySprite_(textureData.getTexture(207)),
	titleText_(),
	totalMoneyText_(),
	backdrop_(textureData),
	fuelUpgradeUI_(
		Config::windowWidth * 0.35f / Config::globalScale - Config::windowWidth * 0.6f / Config::globalScale * 0.5f,
		Config::windowHeight * 0.45f / Config::globalScale - 4.0f,
		Config::windowWidth * 0.6f / Config::globalScale,
		8.0f,
		fuelUpgrade,
		textureData.getTexture(203),
		textureData.getTexture(202),
		textureData.getTexture(201),
		textureData.getTexture(306),
		textureData.getTexture(305)),
	drillUpgradeUI_(
		Config::windowWidth * 0.35f / Config::globalScale - Config::windowWidth * 0.6f / Config::globalScale * 0.5f,
		Config::windowHeight * 0.45f / Config::globalScale - 4.0f + 9.0f,
		Config::windowWidth * 0.6f / Config::globalScale,
		8.0f,
		drillUpgrade,
		textureData.getTexture(209),
		textureData.getTexture(202),
		textureData.getTexture(201),
		textureData.getTexture(306),
		textureData.getTexture(305)),
	speedUpgradeUI_(
		Config::windowWidth * 0.35f / Config::globalScale - Config::windowWidth * 0.6f / Config::globalScale * 0.5f,
		Config::windowHeight * 0.45f / Config::globalScale - 4.0f + 18.0f,
		Config::windowWidth * 0.6f / Config::globalScale,
		8.0f,
		speedUpgrade,
		textureData.getTexture(208),
		textureData.getTexture(202),
		textureData.getTexture(201),
		textureData.getTexture(306),
		textureData.getTexture(305)),
	menuButton_(
		Config::windowWidth * 0.5f / Config::globalScale - 8.0f,
		Config::windowHeight * 0.85f / Config::globalScale - 8.0f, textureData.getTexture(304))
{
	totalMoneySprite_.setPosition(1.0f, 1.0f);

	titleText_.setFont(FontData::getInstance().getFont());
	titleText_.setCharacterSize(Config::largeFontSize);
	titleText_.setFillColor(sf::Color(236, 236, 236));
	titleText_.setOutlineColor(sf::Color(0, 0, 0));
	titleText_.setOutlineThickness(Config::globalScale);
	titleText_.setString("UPGRADES");
	titleText_.setOrigin(
		titleText_.getLocalBounds().left + titleText_.getLocalBounds().width * 0.5f,
		titleText_.getLocalBounds().top + titleText_.getLocalBounds().height * 0.5f);
	titleText_.setPosition(Config::windowWidth * 0.5f, Config::windowHeight * 0.25f);

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

	fuelUpgradeUI_.updateOnMoneyChange(totalMoney_);
	drillUpgradeUI_.updateOnMoneyChange(totalMoney_);
	speedUpgradeUI_.updateOnMoneyChange(totalMoney_);

	SoundData::getInstance().playMusic(4);
}

void Upgrades::update(float deltaTime)
{
	menuButton_.update(deltaTime);

	if (fuelUpgradeUI_.canBuy(totalMoney_)) fuelUpgradeUI_.update(deltaTime);
	if (drillUpgradeUI_.canBuy(totalMoney_)) drillUpgradeUI_.update(deltaTime);
	if (speedUpgradeUI_.canBuy(totalMoney_)) speedUpgradeUI_.update(deltaTime);
}

void Upgrades::updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button)
{
	if (menuButton_.isPressed(mouseX, mouseY, button))
	{
		SoundData::getInstance().playSound(5);
		EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::Menu));
	}
	else if (fuelUpgradeUI_.updateOnMousePress(mouseX, mouseY, button, totalMoney_)
		|| drillUpgradeUI_.updateOnMousePress(mouseX, mouseY, button, totalMoney_)
		|| speedUpgradeUI_.updateOnMousePress(mouseX, mouseY, button, totalMoney_))
	{
		fuelUpgradeUI_.updateOnMoneyChange(totalMoney_);
		drillUpgradeUI_.updateOnMoneyChange(totalMoney_);
		speedUpgradeUI_.updateOnMoneyChange(totalMoney_);

		totalMoneyText_.setString(std::to_string(totalMoney_));
		totalMoneyText_.setOrigin(
			totalMoneyText_.getLocalBounds().left,
			totalMoneyText_.getLocalBounds().top + totalMoneyText_.getLocalBounds().height * 0.5f);
		totalMoneyText_.setPosition(11.0f * Config::globalScale, 5.0f * Config::globalScale);
	}
}

void Upgrades::updateOnMouseMove(int mouseX, int mouseY)
{
	menuButton_.updateOnMouseMove(mouseX, mouseY);

	fuelUpgradeUI_.updateOnMouseMove(mouseX, mouseY);
	drillUpgradeUI_.updateOnMouseMove(mouseX, mouseY);
	speedUpgradeUI_.updateOnMouseMove(mouseX, mouseY);
}

void Upgrades::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::globalScale, Config::globalScale);

	target.draw(backdrop_, states);

	target.draw(totalMoneySprite_, states);

	target.draw(titleText_);
	target.draw(totalMoneyText_);

	target.draw(fuelUpgradeUI_, states);
	target.draw(drillUpgradeUI_, states);
	target.draw(speedUpgradeUI_, states);

	target.draw(menuButton_, states);
}