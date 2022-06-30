#pragma once

#include <SFML/Graphics/Font.hpp>

class FontData
{
public:
	FontData(const FontData &other) = delete;
	FontData &operator=(const FontData &other) = delete;

	static FontData &getInstance();

	const sf::Font &getFont() const;
private:
	FontData();
	~FontData() {}

	sf::Font font_;
};