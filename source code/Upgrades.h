#pragma once

class TextureData;

#include "DriverState.h"
#include "Backdrop.h"
#include "UpgradeUI.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class Upgrades : public DriverState
{
public:
	Upgrades(
		uint64_t &totalMoney,
		Upgrade &fuelUpgrade,
		Upgrade &drillUpgrade,
		Upgrade &speedUpgrade,
		const TextureData &textureData);

	void update(float deltaTime);
	void updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	uint64_t &totalMoney_;

	sf::Sprite totalMoneySprite_;

	sf::Text titleText_;
	sf::Text totalMoneyText_;

	Backdrop backdrop_;

	UpgradeUI fuelUpgradeUI_;
	UpgradeUI drillUpgradeUI_;
	UpgradeUI speedUpgradeUI_;

	Button menuButton_;
};