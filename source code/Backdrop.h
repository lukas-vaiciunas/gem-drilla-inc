#pragma once

class TextureData;

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class Backdrop : public sf::Drawable
{
public:
	Backdrop(const TextureData &textureData);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	std::vector<sf::Sprite> sprites_;

	void setup_(const TextureData &textureData);
};