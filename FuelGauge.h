#pragma once

#include "Timer.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class FuelGauge : public sf::Drawable
{
public:
	FuelGauge(
		uint8_t numFuel,
		float drainSecs,
		const sf::Texture &gasCanTexture,
		const sf::Texture &indicatorFullTexture,
		const sf::Texture &indicatorEmptyTexture);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isEmpty() const;
private:
	const sf::Texture &indicatorEmptyTexture_;

	std::vector<sf::Sprite> indicatorSprites_;
	sf::Sprite gasCanSprite_;

	Timer drainTimer_;

	const uint8_t maxFuel_;
	uint8_t numFuel_;
};