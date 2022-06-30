#pragma once

#include "DriverState.h"
#include "Listener.h"
#include "GameState.h"
#include "GameStateType.h"
#include "ParticlePool.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "FuelGauge.h"
#include "DepthGauge.h"
#include "ProfitGauge.h"

class Game :
	public DriverState,
	public Listener
{
public:
	Game(uint8_t numFuel, float drillDPS, float playerSpeed, const TextureData &textureData);
	~Game();

	void onEvent(const Event &ev) override;

	void update(float deltaTime) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	friend class PlayGameState;
	friend class DeathGameState;

	const TextureData &textureData_;

	GameState *state_;
	GameStateType stateType_;

	ParticlePool particlePool_;
	Map map_;
	Player player_;
	Camera camera_;
	FuelGauge fuelGauge_;
	DepthGauge depthGauge_;
	ProfitGauge profitGauge_;

	void changeState_(GameStateType toStateType);
};