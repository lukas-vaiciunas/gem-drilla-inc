#pragma once

class Particle;
class TextureData;

#include <SFML/Graphics/Drawable.hpp>
#include <vector>

class ParticlePool : public sf::Drawable
{
public:
	ParticlePool(size_t capacity);
	~ParticlePool();

	void update(float deltaTime);

	void add(Particle *particle);

	void spawnBlockHitEffect(float x, float y, const TextureData &textureData);
	void spawnBlockBreakEffect(float x, float y, const TextureData &textureData);
	void spawnDeathEffect(float x, float y, const TextureData &textureData);
	void spawnExplosionEffect(float x, float y, const TextureData &textureData);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isFull() const;
private:
	std::vector<Particle *> particles_;
	size_t capacity_;
	size_t numLive_;

	void removeAtIndex_(size_t index);
};