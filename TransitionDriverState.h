#pragma once

class GameData;
class TextureData;

#include "DriverState.h"
#include "DriverStateType.h"
#include <SFML/Graphics/RectangleShape.hpp>

class TransitionDriverState : public DriverState
{
public:
	TransitionDriverState(
		DriverState *beginState,
		DriverStateType endStateType,
		GameData &gameData,
		const TextureData &textureData);

	~TransitionDriverState();

	void update(float deltaTime) override;
	void updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	enum class TransitionState : uint8_t
	{
		FadeIn,
		FadeOut,
		Done
	};

	const TextureData &textureData_;
	GameData &gameData_;

	TransitionState transitionState_;

	DriverState *state_;
	DriverStateType endStateType_;

	sf::RectangleShape overlay_;

	float alpha_;
	float velAlpha_;

	void advanceState_();
};