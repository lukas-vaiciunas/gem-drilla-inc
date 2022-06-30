#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class DepthGauge : public sf::Drawable
{
public:
	DepthGauge(const sf::Texture &depthTexture);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setDepth(uint8_t depth);

	uint8_t getMaxDepth() const;
private:
	sf::Sprite depthSprite_;
	sf::Text text_;
	uint8_t depth_;
	uint8_t maxDepth_;

	void forceSetDepth_(uint8_t depth);
};