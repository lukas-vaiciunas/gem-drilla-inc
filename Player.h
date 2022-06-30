#pragma once

class TextureData;
class Map;

#include "PlayerState.h"
#include "Direction.h"
#include "PlayerSprite.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player : public sf::Drawable
{
public:
	Player(int mapCol, int mapRow, float dps, float speed, const sf::Texture &texture, Map &map);
	~Player();

	void update(float deltaTime);
	void updateOnKeyPress(sf::Keyboard::Key key);
	void updateOnKeyRelease(sf::Keyboard::Key key);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	int getMapCol() const;
	int getMapRow() const;
	float getX() const;
	float getY() const;
private:
	friend class WaitPlayerState;
	friend class MovePlayerState;
	friend class DigPlayerState;

	Map &map_;

	PlayerState *state_;
	PlayerSprite sprite_;

	int mapCol_;
	int mapRow_;

	bool isMovingUp_;
	bool isMovingDown_;
	bool isMovingLeft_;
	bool isMovingRight_;

	float dps_;
	float speed_;

	Direction verifyMovement_();
	Direction verifyDigging_();
	void changeState_(PlayerState *state);
};