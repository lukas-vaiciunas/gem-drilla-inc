#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Tile : public sf::Drawable
{
public:
	Tile(int mapCol, int mapRow, const sf::Texture &tileTexture);
	virtual ~Tile() {}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	int getMapCol() const;
	int getMapRow() const;
private:
	sf::Sprite sprite_;
	int mapCol_;
	int mapRow_;
};