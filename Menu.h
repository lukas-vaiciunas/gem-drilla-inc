#pragma once

class TextureData;

#include "DriverState.h"
#include "Backdrop.h"
#include "Button.h"
#include <SFML/Graphics/Text.hpp>

class Menu : public DriverState
{
public:
	Menu(uint64_t totalMoney, uint8_t maxDepth, const TextureData &textureData);

	void update(float deltaTime) override;
	void updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	Backdrop backdrop_;

	Button playButton_;
	Button upgradeButton_;
	Button quitButton_;

	sf::Sprite totalMoneySprite_;
	sf::Sprite maxDepthSprite_;

	sf::Text totalMoneyText_;
	sf::Text maxDepthText_;

	sf::Text gemText_;
	sf::Text drillaText_;
	sf::Text incText_;

	sf::Text copyrightText_;
};