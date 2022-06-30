#include "Results.h"
#include "TextureData.h"
#include "EventQueue.h"
#include "Event.h"
#include "FontData.h"
#include "SoundData.h"
#include "Config.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

Results::Results(uint64_t lastProfit, uint8_t lastMaxDepth, const TextureData &textureData) :
	DriverState(DriverStateType::Results),
	backdrop_(textureData),
	menuButton_(Config::windowWidth * 0.5f / Config::globalScale - 8.0f, Config::windowHeight * 0.85f / Config::globalScale - 8.0f, textureData.getTexture(304)),
	moneySprite_(textureData.getTexture(205)),
	depthSprite_(textureData.getTexture(204)),
	titleText_(),
	profitText_(),
	maxDepthText_()
{
	moneySprite_.setPosition(
		Config::windowWidth * 0.25f / Config::globalScale,
		Config::windowHeight * 0.5f / Config::globalScale - 4.0f);

	depthSprite_.setPosition(
		Config::windowWidth * 0.25f / Config::globalScale,
		Config::windowHeight * 0.5f / Config::globalScale - 4.0f + 9.0f);

	titleText_.setFont(FontData::getInstance().getFont());
	titleText_.setCharacterSize(Config::largeFontSize);
	titleText_.setFillColor(sf::Color(192, 88, 88));
	titleText_.setOutlineColor(sf::Color(0, 0, 0));
	titleText_.setOutlineThickness(Config::globalScale);
	titleText_.setString("OUT OF FUEL!");
	titleText_.setOrigin(
		titleText_.getLocalBounds().left + titleText_.getLocalBounds().width * 0.5f,
		titleText_.getLocalBounds().top + titleText_.getLocalBounds().height * 0.5f);
	titleText_.setPosition(Config::windowWidth * 0.5f, Config::windowHeight * 0.25f);

	profitText_.setFont(FontData::getInstance().getFont());
	profitText_.setCharacterSize(Config::mediumFontSize);
	profitText_.setFillColor(sf::Color(236, 236, 236));
	profitText_.setOutlineColor(sf::Color(0, 0, 0));
	profitText_.setOutlineThickness(Config::globalScale);
	profitText_.setString(std::to_string(lastProfit));
	profitText_.setOrigin(
		profitText_.getLocalBounds().left,
		profitText_.getLocalBounds().top + profitText_.getLocalBounds().height * 0.5f);
	profitText_.setPosition(
		Config::windowWidth * 0.25f + 10.0f * Config::globalScale,
		Config::windowHeight * 0.5f);

	maxDepthText_.setFont(FontData::getInstance().getFont());
	maxDepthText_.setCharacterSize(Config::mediumFontSize);
	maxDepthText_.setFillColor(sf::Color(236, 236, 236));
	maxDepthText_.setOutlineColor(sf::Color(0, 0, 0));
	maxDepthText_.setOutlineThickness(Config::globalScale);
	maxDepthText_.setString(std::to_string(lastMaxDepth));
	maxDepthText_.setOrigin(
		maxDepthText_.getLocalBounds().left,
		maxDepthText_.getLocalBounds().top + maxDepthText_.getLocalBounds().height * 0.5f);
	maxDepthText_.setPosition(
		Config::windowWidth * 0.25f + 10.0f * Config::globalScale,
		Config::windowHeight * 0.5f + 9.0f * Config::globalScale);

	SoundData::getInstance().playMusic(3);
}

void Results::update(float deltaTime)
{
	menuButton_.update(deltaTime);
}

void Results::updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button)
{
	if (menuButton_.isPressed(mouseX, mouseY, button))
	{
		SoundData::getInstance().playSound(5);
		EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::Menu));
	}
}

void Results::updateOnMouseMove(int mouseX, int mouseY)
{
	menuButton_.updateOnMouseMove(mouseX, mouseY);
}

void Results::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::globalScale, Config::globalScale);

	target.draw(backdrop_, states);

	target.draw(titleText_);
	target.draw(profitText_);
	target.draw(maxDepthText_);

	target.draw(moneySprite_, states);
	target.draw(depthSprite_, states);
	target.draw(menuButton_, states);
}