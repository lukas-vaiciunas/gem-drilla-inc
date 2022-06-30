#include "Tile.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

Tile::Tile(int mapCol, int mapRow, const sf::Texture &tileTexture) :
	sf::Drawable(),
	sprite_(tileTexture),
	mapCol_(mapCol),
	mapRow_(mapRow)
{
	sprite_.setPosition(
		static_cast<float>(mapCol * Constants::tileSize),
		static_cast<float>(mapRow * Constants::tileSize));
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

int Tile::getMapCol() const
{
	return mapCol_;
}

int Tile::getMapRow() const
{
	return mapRow_;
}