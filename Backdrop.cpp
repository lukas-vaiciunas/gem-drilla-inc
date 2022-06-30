#include "Backdrop.h"
#include "Config.h"
#include "Constants.h"
#include "TextureData.h"
//#include "RandGen.h"
#include <SFML/Graphics/RenderTarget.hpp>

Backdrop::Backdrop(const TextureData &textureData) :
	sf::Drawable()
{
	this->setup_(textureData);
}

void Backdrop::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const sf::Sprite &sprite : sprites_)
	{
		target.draw(sprite, states);
	}
}

void Backdrop::setup_(const TextureData &textureData)
{
	float scaleRatio = 1.0f / Config::globalScale;
	float spacing = Constants::tileSize * Config::globalScale;

	const sf::Texture &stoneTexture = textureData.getTexture(11);
	/*const sf::Texture &rubyTexture = textureData.getTexture(16);
	const sf::Texture &emeraldTexture = textureData.getTexture(17);
	const sf::Texture &sapphireTexture = textureData.getTexture(18);

	std::mt19937 &eng = RandGen::getInstance().getEng();
	std::uniform_int_distribution<uint16_t> chanceDis(1, 1000);*/

	for (float y = 0.0f; y < Config::windowHeight; y += spacing)
	{
		for (float x = 0.0f; x < Config::windowWidth; x += spacing)
		{
			sf::Sprite sprite(stoneTexture);

			/*uint16_t roll = chanceDis(eng);

			if (roll <= 10)
			{
				sprite.setTexture(sapphireTexture);
			}
			else if (roll <= 20)
			{
				sprite.setTexture(emeraldTexture);
			}
			else if (roll <= 30)
			{
				sprite.setTexture(rubyTexture);
			}
			else
			{
				sprite.setTexture(stoneTexture);
			}*/

			sprite.setPosition(x * scaleRatio, y * scaleRatio);
			sprites_.push_back(std::move(sprite));
		}
	}
}