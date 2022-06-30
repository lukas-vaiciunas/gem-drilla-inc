#pragma once

#include "DriverState.h"
#include "DriverStateType.h"
#include "Listener.h"
#include "TextureData.h"
#include "GameData.h"

class Driver :
	public DriverState,
	public Listener
{
public:
	Driver();
	~Driver();

	void onEvent(const Event &ev) override;

	void update(float deltaTime) override;
	void updateOnMousePress(int mouseX, int mouseY, sf::Mouse::Button button) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isDone() const;
private:
	DriverState *state_;
	DriverStateType stateType_;
	
	TextureData textureData_;

	GameData gameData_;

	bool isDone_;

	void changeState_(DriverStateType toStateType);
	void changeState_(DriverState *toState);
};