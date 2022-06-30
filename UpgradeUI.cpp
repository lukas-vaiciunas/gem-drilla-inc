#include "UpgradeUI.h"
#include "Upgrade.h"
#include "FontData.h"
#include "SoundData.h"
#include "Config.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

UpgradeUI::UpgradeUI(
	float x, float y, float width, float height,
	Upgrade &upgrade,
	const sf::Texture &upgradeTexture,
	const sf::Texture &indicatorEmptyTexture,
	const sf::Texture &indicatorFullTexture,
	const sf::Texture &buttonUnavailableTexture,
	const sf::Texture &buttonAvailableTexture)
	:
	indicatorFullTexture_(indicatorFullTexture),
	buttonUnavailableTexture_(buttonUnavailableTexture),
	buttonAvailableTexture_(buttonAvailableTexture),
	upgrade_(upgrade),
	x_(x),
	y_(y),
	width_(width),
	height_(height),
	indicatorSprites_(upgrade.getMaxLevel(), sf::Sprite(indicatorEmptyTexture)),
	upgradeSprite_(upgradeTexture),
	costText_(),
	button_(x + width - 8.0f, y + height * 0.5f - 4.0f, buttonUnavailableTexture)
{
	upgradeSprite_.setPosition(x, y + height * 0.5f - 4.0f);

	for (uint8_t i = 0; i < upgrade.getMaxLevel(); ++i)
	{
		indicatorSprites_[i].setPosition(x + 9.0f + 5.0f * i, y + height * 0.5f - 2.0f);
	}

	for (uint8_t i = 0; i < upgrade.getLevel(); ++i)
	{
		indicatorSprites_[i].setTexture(indicatorFullTexture);
	}

	costText_.setFont(FontData::getInstance().getFont());
	costText_.setCharacterSize(Config::mediumFontSize);
	costText_.setFillColor(sf::Color(236, 236, 236));
	costText_.setOutlineColor(sf::Color(0, 0, 0));
	costText_.setOutlineThickness(Config::globalScale);

	this->updateCostText_();
}

void UpgradeUI::updateOnMoneyChange(uint64_t totalMoney)
{
	if (upgrade_.getLevel() < upgrade_.getMaxLevel()
		&& upgrade_.getCost() <= totalMoney)
	{
		button_.setTexture(buttonAvailableTexture_);
	}
	else
	{
		button_.setTexture(buttonUnavailableTexture_);
	}
}

void UpgradeUI::update(float deltaTime)
{
	button_.update(deltaTime);
}

bool UpgradeUI::updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button, uint64_t &totalMoney)
{
	if (button_.isPressed(mouseX, mouseY, button)
		&& this->canBuy(totalMoney))
	{
		totalMoney -= upgrade_.getCost();
		indicatorSprites_[upgrade_.getLevel()].setTexture(indicatorFullTexture_);
		upgrade_.unlock();

		SoundData::getInstance().playSound(4);

		this->updateCostText_();

		return true;
	}

	return false;
}

void UpgradeUI::updateOnMouseMove(int mouseX, int mouseY)
{
	button_.updateOnMouseMove(mouseX, mouseY);
}

void UpgradeUI::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (upgrade_.getLevel() < upgrade_.getMaxLevel())
	{
		target.draw(costText_);
	}

	target.draw(upgradeSprite_, states);

	for (const sf::Sprite &sprite : indicatorSprites_)
	{
		target.draw(sprite, states);
	}

	target.draw(button_, states);
}

bool UpgradeUI::canBuy(uint64_t totalMoney) const
{
	return upgrade_.getCost() <= totalMoney
		&& upgrade_.getLevel() < upgrade_.getMaxLevel();
}

void UpgradeUI::updateCostText_()
{
	costText_.setString("($" + std::to_string(upgrade_.getCost()) + ")");
	costText_.setOrigin(
		costText_.getLocalBounds().left,
		costText_.getLocalBounds().top + costText_.getLocalBounds().height * 0.5f);
	costText_.setPosition((x_ + width_ + 1.0f) * Config::globalScale, (y_ + height_ * 0.5f) * Config::globalScale);
}