#include "MinableTile.h"
#include "ParticlePool.h"
#include "SoundData.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

MinableTile::MinableTile(
	int mapCol, int mapRow,
	float health,
	uint64_t value,
	const sf::Texture &tileTexture,
	const sf::Texture &digTexture)
	:
	Tile(mapCol, mapRow, tileTexture),
	digSprite_(digTexture),
	maxHealth_(health),
	health_(health),
	value_(value)
{
	digSprite_.setPosition(
		static_cast<float>(mapCol * Constants::tileSize),
		static_cast<float>(mapRow * Constants::tileSize));
	digSprite_.setTextureRect(sf::IntRect(0, 0, 8, 8));
}

void MinableTile::dig(float damage, ParticlePool &particlePool, const TextureData &textureData)
{
	float oldHealthRatio = health_ / maxHealth_;

	health_ -= damage;

	float newHealthRatio = health_ / maxHealth_;

	if (oldHealthRatio > 0.2f && newHealthRatio <= 0.2f)
	{
		digSprite_.setTextureRect(sf::IntRect(24, 0, 8, 8));

		particlePool.spawnBlockHitEffect((
			this->getMapCol() + 0.5f) * Constants::tileSize,
			(this->getMapRow() + 0.5f) * Constants::tileSize,
			textureData);

		SoundData::getInstance().playSound(1);
	}
	else if (oldHealthRatio > 0.4f && newHealthRatio <= 0.4f)
	{
		digSprite_.setTextureRect(sf::IntRect(16, 0, 8, 8));

		particlePool.spawnBlockHitEffect((
			this->getMapCol() + 0.5f) * Constants::tileSize,
			(this->getMapRow() + 0.5f) * Constants::tileSize,
			textureData);

		SoundData::getInstance().playSound(1);
	}
	else if (oldHealthRatio > 0.6f && newHealthRatio <= 0.6f)
	{
		digSprite_.setTextureRect(sf::IntRect(8, 0, 8, 8));

		particlePool.spawnBlockHitEffect((
			this->getMapCol() + 0.5f) * Constants::tileSize,
			(this->getMapRow() + 0.5f) * Constants::tileSize,
			textureData);

		SoundData::getInstance().playSound(1);
	}
	else if (oldHealthRatio > 0.8f && newHealthRatio <= 0.8f)
	{
		digSprite_.setTextureRect(sf::IntRect(0, 0, 8, 8));

		particlePool.spawnBlockHitEffect((
			this->getMapCol() + 0.5f) * Constants::tileSize,
			(this->getMapRow() + 0.5f) * Constants::tileSize,
			textureData);

		SoundData::getInstance().playSound(1);
	}
}

void MinableTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	Tile::draw(target, states);

	if (health_ <= maxHealth_ * 0.8f)
	{
		target.draw(digSprite_, states);
	}
}

float MinableTile::getHealth() const
{
	return health_;
}

uint64_t MinableTile::getValue() const
{
	return value_;
}