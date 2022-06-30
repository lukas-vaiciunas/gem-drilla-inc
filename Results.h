#pragma once

class TextureData;

#include "DriverState.h"
#include "Backdrop.h"
#include "Button.h"
#include <SFML/Graphics/Text.hpp>

class Results : public DriverState
{
public:
	Results(uint64_t lastProfit, uint8_t lastMaxDepth, const TextureData &textureData);

	void update(float deltaTime) override;
	void updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	Backdrop backdrop_;

	Button menuButton_;

	sf::Sprite moneySprite_;
	sf::Sprite depthSprite_;

	sf::Text titleText_;
	sf::Text profitText_;
	sf::Text maxDepthText_;
};