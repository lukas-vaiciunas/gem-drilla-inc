#include "ProfitGauge.h"
#include "FontData.h"
#include "Config.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

ProfitGauge::ProfitGauge(const sf::Texture &moneyTexture) :
	sf::Drawable(),
	moneySprite_(moneyTexture),
	text_(),
	profit_(-1)
{
	moneySprite_.setPosition(1.0f, 19.0f);

	text_.setFont(FontData::getInstance().getFont());
	text_.setCharacterSize(Config::mediumFontSize);
	text_.setFillColor(sf::Color(236, 236, 236));
	text_.setOutlineColor(sf::Color(0, 0, 0));
	text_.setOutlineThickness(Config::globalScale);

	this->setProfit_(0);
}

void ProfitGauge::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(moneySprite_, states);
	target.draw(text_);
}

void ProfitGauge::addProfit(uint64_t profit)
{
	this->setProfit_(profit_ + profit);
}

uint64_t ProfitGauge::getProfit() const
{
	return profit_;
}

void ProfitGauge::setProfit_(uint64_t profit)
{
	profit_ = profit;

	text_.setString(std::to_string(profit_));
	text_.setOrigin(
		text_.getLocalBounds().left,
		text_.getLocalBounds().top + text_.getLocalBounds().height * 0.5f);
	text_.setPosition(11.0f * Config::globalScale, 23.0f * Config::globalScale);
}