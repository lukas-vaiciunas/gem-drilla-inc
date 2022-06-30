#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class ProfitGauge : public sf::Drawable
{
public:
	ProfitGauge(const sf::Texture &moneyTexture);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void addProfit(uint64_t profit);

	uint64_t getProfit() const;
private:
	sf::Sprite moneySprite_;
	sf::Text text_;
	uint64_t profit_;

	void setProfit_(uint64_t profit);
};