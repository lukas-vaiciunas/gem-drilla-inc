#pragma once

class Upgrade;

#include "Button.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

class UpgradeUI : public sf::Drawable
{
public:
	UpgradeUI(
		float x, float y, float width, float height,
		Upgrade &upgrade,
		const sf::Texture &upgradeTexture,
		const sf::Texture &indicatorEmptyTexture,
		const sf::Texture &indicatorFullTexture,
		const sf::Texture &buttonUnavailableTexture,
		const sf::Texture &buttonAvailableTexture);

	void updateOnMoneyChange(uint64_t totalMoney);
	void update(float deltaTime);
	bool updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button, uint64_t &totalMoney);
	void updateOnMouseMove(int mouseX, int mouseY);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool canBuy(uint64_t totalMoney) const;
private:
	const sf::Texture &indicatorFullTexture_;
	const sf::Texture &buttonUnavailableTexture_;
	const sf::Texture &buttonAvailableTexture_;

	Upgrade &upgrade_;

	float x_;
	float y_;
	float width_;
	float height_;

	std::vector<sf::Sprite> indicatorSprites_;

	sf::Sprite upgradeSprite_;
	
	sf::Text costText_;

	Button button_;

	void updateCostText_();
};