#pragma once

class ParticlePool;
class TextureData;

#include "Tile.h"

class MinableTile : public Tile
{
public:
	MinableTile(
		int mapCol, int mapRow,
		float health,
		uint64_t value,
		const sf::Texture &tileTexture,
		const sf::Texture &digTexture);

	void dig(float damage, ParticlePool &particlePool, const TextureData &textureData);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	float getHealth() const;
	uint64_t getValue() const;
private:
	sf::Sprite digSprite_;
	float maxHealth_;
	float health_;
	uint64_t value_;
};