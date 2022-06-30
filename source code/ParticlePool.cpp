#include "ParticlePool.h"
#include "Particle.h"
#include "TextureData.h"
#include "RandGen.h"
#include <SFML/Graphics/RenderTarget.hpp>

ParticlePool::ParticlePool(size_t capacity) :
	sf::Drawable(),
	particles_(capacity, nullptr),
	capacity_(capacity),
	numLive_(0)
{}

ParticlePool::~ParticlePool()
{
	for (size_t i = 0; i < numLive_; ++i)
	{
		delete particles_[i];
	}
}

void ParticlePool::update(float deltaTime)
{
	for (size_t i = 0; i < numLive_; )
	{
		particles_[i]->update(deltaTime);

		if (particles_[i]->isDead())
		{
			this->removeAtIndex_(i);
		}
		else ++i;
	}
}

void ParticlePool::add(Particle *particle)
{
	particles_[numLive_++] = particle;
}

void ParticlePool::spawnBlockHitEffect(float x, float y, const TextureData &textureData)
{
	std::mt19937 &eng = RandGen::getInstance().getEng();

	std::uniform_real_distribution<float> velDis(-16.0f, 16.0f);

	for (int i = 0; i < 3; ++i)
	{
		if (this->isFull()) break;

		this->add(new Particle(x, y, velDis(eng), velDis(eng), velDis(eng), 0.0f, 16.0f, 1.0f, textureData.getTexture(103)));
	}
}

void ParticlePool::spawnBlockBreakEffect(float x, float y, const TextureData &textureData)
{
	std::mt19937 &eng = RandGen::getInstance().getEng();

	std::uniform_real_distribution<float> velDis(-16.0f, 16.0f);

	for (int i = 0; i < 10; ++i)
	{
		if (this->isFull()) break;

		this->add(new Particle(x, y, velDis(eng), velDis(eng), velDis(eng), 0.0f, 16.0f, 1.0f, textureData.getTexture(103)));
	}
}

void ParticlePool::spawnDeathEffect(float x, float y, const TextureData &textureData)
{
	this->spawnExplosionEffect(x, y, textureData);

	if (!this->isFull())
	{
		this->add(new Particle(x, y, -16.0f, -32.0f, -360.0f, 0.0f, 32.0f, 8.0f, textureData.getTexture(101)));
	}
	if (!this->isFull())
	{
		this->add(new Particle(x, y, 16.0f, -32.0f, 360.0f, 0.0f, 32.0f, 8.0f, textureData.getTexture(102)));
	}
}

void ParticlePool::spawnExplosionEffect(float x, float y, const TextureData &textureData)
{
	std::mt19937 &eng = RandGen::getInstance().getEng();

	std::vector<uint16_t> textureIds({
		104,
		105,
		106
	});

	std::uniform_real_distribution<float> velDis(-32.0f, 32.0f);
	std::uniform_int_distribution<size_t> textureIdIndexDis(0, textureIds.size() - 1);

	for (int i = 0; i < 50; ++i)
	{
		if (this->isFull()) break;

		this->add(new Particle(x, y, velDis(eng), velDis(eng), velDis(eng), 0.0f, 0.0f, 8.0f, textureData.getTexture(textureIds[textureIdIndexDis(eng)])));
	}
}

void ParticlePool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (size_t i = 0; i < numLive_; ++i)
	{
		target.draw(*particles_[i], states);
	}
}

bool ParticlePool::isFull() const
{
	return numLive_ == capacity_;
}

void ParticlePool::removeAtIndex_(size_t index)
{
	delete particles_[index];
	particles_[index] = particles_[--numLive_];
}