#pragma once

#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>

class TextureData
{
public:
	TextureData(const std::string &textureDataPath);

	const sf::Texture &getTexture(uint16_t id) const;
private:
	std::unordered_map<uint16_t, sf::Texture> textures_;

	void loadTexturesFromFile_(const std::string &path);
};