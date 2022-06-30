#include "TextureData.h"
#include <fstream>

TextureData::TextureData(const std::string &textureDataPath)
{
	this->loadTexturesFromFile_(textureDataPath);
}

const sf::Texture &TextureData::getTexture(uint16_t id) const
{
	return textures_.find(id)->second;
}

void TextureData::loadTexturesFromFile_(const std::string &path)
{
	std::ifstream in(path, std::ios_base::in);

	if (!in.is_open())
	{
		printf("Failed to open %s in TextureData!\n", path.c_str());
		return;
	}

	uint16_t numTextures;
	uint16_t textureId;
	std::string texturePath;

	in >> numTextures;

	while (numTextures--)
	{
		in >> textureId >> texturePath;

		sf::Texture tex;
		tex.loadFromFile(texturePath);

		textures_.emplace(textureId, std::move(tex));
	}

	in.close();
}