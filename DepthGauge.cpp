#include "DepthGauge.h"
#include "FontData.h"
#include "Config.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

DepthGauge::DepthGauge(const sf::Texture &depthTexture) :
	sf::Drawable(),
	depthSprite_(depthTexture),
	depth_(0),
	maxDepth_(0)
{
	depthSprite_.setPosition(1.0f, 10.0f);

	text_.setFont(FontData::getInstance().getFont());
	text_.setCharacterSize(Config::mediumFontSize);
	text_.setFillColor(sf::Color(236, 236, 236));
	text_.setOutlineColor(sf::Color(0, 0, 0));
	text_.setOutlineThickness(Config::globalScale);

	this->forceSetDepth_(0);
}

void DepthGauge::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(depthSprite_, states);
	target.draw(text_);
}

void DepthGauge::setDepth(uint8_t depth)
{
	if (depth_ == depth) return;

	this->forceSetDepth_(depth);
}

uint8_t DepthGauge::getMaxDepth() const
{
	return maxDepth_;
}

void DepthGauge::forceSetDepth_(uint8_t depth)
{
	depth_ = depth;
	maxDepth_ = std::max(maxDepth_, depth_);

	text_.setString(std::to_string(depth_));
	text_.setOrigin(
		text_.getLocalBounds().left,
		text_.getLocalBounds().top + text_.getLocalBounds().height * 0.5f);
	text_.setPosition(11.0f * Config::globalScale, 14.0f * Config::globalScale);
}