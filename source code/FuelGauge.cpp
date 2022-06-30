#include "FuelGauge.h"
#include <SFML/Graphics/RenderTarget.hpp>

FuelGauge::FuelGauge(
	uint8_t numFuel,
	float drainSecs,
	const sf::Texture &gasCanTexture,
	const sf::Texture &indicatorFullTexture,
	const sf::Texture &indicatorEmptyTexture)
	:
	sf::Drawable(),
	indicatorEmptyTexture_(indicatorEmptyTexture),
	indicatorSprites_(numFuel, sf::Sprite(indicatorFullTexture)),
	gasCanSprite_(gasCanTexture),
	drainTimer_(drainSecs),
	maxFuel_(numFuel),
	numFuel_(numFuel)
{
	gasCanSprite_.setPosition(1.0f, 1.0f);

	for (uint8_t i = 0; i < numFuel; ++i)
	{
		indicatorSprites_[i].setPosition(10.0f + 5.0f * i, 3.0f);
	}
}

void FuelGauge::update(float deltaTime)
{
	drainTimer_.update(deltaTime);

	if (drainTimer_.isDone())
	{
		drainTimer_.reset();

		indicatorSprites_[--numFuel_].setTexture(indicatorEmptyTexture_);
	}
}

void FuelGauge::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(gasCanSprite_, states);

	for (size_t i = 0; i < maxFuel_; ++i)
	{
		target.draw(indicatorSprites_[i], states);
	}
}

bool FuelGauge::isEmpty() const
{
	return numFuel_ == 0;
}