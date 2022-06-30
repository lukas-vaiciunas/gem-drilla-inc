#include "Map.h"
#include "TextureData.h"
#include "ParticlePool.h"
#include "RandGen.h"
#include "Tile.h"
#include "EventQueue.h"
#include "Event.h"
#include "SoundData.h"
#include "Config.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

Map::Map(uint16_t numCols, uint16_t numRows, const TextureData &textureData, ParticlePool &particlePool) :
	sf::Drawable(),
	textureData_(textureData),
	particlePool_(particlePool),
	minableTilePartition_(numCols / 15, numRows / 15, 15),
	visibleMinableTiles_(),
	scenicTilePartition_(numCols / 15, numRows / 15, 15),
	visibleScenicTiles_(),
	gridPartitionCoords_(0, 0),
	numCols_(numCols),
	numRows_(numRows)
{
	this->generate_();
}

void Map::dig(int col, int row, float damage)
{
	MinableTile &tile = minableTilePartition_.getObjectRef(col, row);
	tile.dig(damage, particlePool_, textureData_);

	if (tile.getHealth() <= 0.0f)
	{
		EventQueue::getInstance().send(new EventBlockMined(tile.getValue()));

		minableTilePartition_.remove(col, row);
		scenicTilePartition_.add(new Tile(col, row, textureData_.getTexture(51)));

		this->forceUpdateVisibility(col, row);

		particlePool_.spawnBlockBreakEffect((col + 0.5f) * Constants::tileSize, (row + 0.5f) * Constants::tileSize, textureData_);
	
		SoundData::getInstance().playSound(2);
	}
}

void Map::updateVisibility(int playerMapCol, int playerMapRow)
{
	Coords newGridPartitionCoords = std::move(minableTilePartition_.getCellCoords(playerMapCol, playerMapRow));

	if (gridPartitionCoords_ == newGridPartitionCoords) return;

	gridPartitionCoords_ = newGridPartitionCoords;

	visibleMinableTiles_ = std::move(minableTilePartition_.getObjectsNear(gridPartitionCoords_));
	visibleScenicTiles_ = std::move(scenicTilePartition_.getObjectsNear(gridPartitionCoords_));
}

void Map::forceUpdateVisibility(int playerMapCol, int playerMapRow)
{
	gridPartitionCoords_ = std::move(minableTilePartition_.getCellCoords(playerMapCol, playerMapRow));
	
	visibleMinableTiles_ = std::move(minableTilePartition_.getObjectsNear(gridPartitionCoords_));
	visibleScenicTiles_ = std::move(scenicTilePartition_.getObjectsNear(gridPartitionCoords_));
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const Tile *const tile : visibleScenicTiles_)
	{
		target.draw(*tile, states);
	}

	for (const MinableTile *const tile : visibleMinableTiles_)
	{
		target.draw(*tile, states);
	}
}

bool Map::existsMinableTile(int col, int row) const
{
	return minableTilePartition_.existsObject(col, row);
}

bool Map::isInBounds(int col, int row) const
{
	return col >= 0
		&& row >= 0
		&& col < static_cast<int>(numCols_)
		&& row < static_cast<int>(numRows_);
}

float Map::getWidth() const
{
	return static_cast<float>(numCols_ * Constants::tileSize);
}

float Map::getHeight() const
{
	return static_cast<float>(numRows_ * Constants::tileSize);
}

void Map::generate_()
{
	enum class BlockType : uint8_t
	{
		Stone,
		Coal,
		Copper,
		Iron,
		Gold,
		Ruby,
		Emerald,
		Sapphire
	};

	std::vector<std::pair<BlockType, float>> blockRarities(
		{
			{BlockType::Sapphire, 0.005f},
			{BlockType::Emerald, 0.005f},
			{BlockType::Ruby, 0.005f},
			{BlockType::Gold, 0.01f},
			{BlockType::Iron, 0.05f},
			{BlockType::Copper, 0.07f},
			{BlockType::Coal, 0.09f},
			{BlockType::Stone, 0.765f},
		});

	const sf::Texture &digTexture = textureData_.getTexture(2);
	const sf::Texture &stoneTexture = textureData_.getTexture(11);
	const sf::Texture &coalTexture = textureData_.getTexture(12);
	const sf::Texture &copperTexture = textureData_.getTexture(13);
	const sf::Texture &ironTexture = textureData_.getTexture(14);
	const sf::Texture &goldTexture = textureData_.getTexture(15);
	const sf::Texture &rubyTexture = textureData_.getTexture(16);
	const sf::Texture &emeraldTexture = textureData_.getTexture(17);
	const sf::Texture &sapphireTexture = textureData_.getTexture(18);
	const sf::Texture &grassTexture = textureData_.getTexture(19);
	const sf::Texture &dirtTexture = textureData_.getTexture(20);

	const int dice = 100000;

	std::mt19937 &eng = RandGen::getInstance().getEng();
	std::uniform_int_distribution<int> rollDis(1, dice);
	std::uniform_int_distribution<uint16_t> scenicTileTextureIdDis(52, 58);

	for (uint16_t col = 0; col < numCols_; col += 2)
	{
		scenicTilePartition_.add(new Tile(col, 0, textureData_.getTexture(scenicTileTextureIdDis(eng))));
	}

	for (uint16_t col = 0; col < numCols_; ++col)
	{
		minableTilePartition_.add(new MinableTile(col, 1, 50.0f, 1, grassTexture, digTexture));
		minableTilePartition_.add(new MinableTile(col, 2, 50.0f, 1, dirtTexture, digTexture));
	}

	for (uint16_t row = 3; row < numRows_; ++row)
	{
		for (uint16_t col = 0; col < numCols_; ++col)
		{
			int roll = rollDis(eng);

			for (const std::pair<BlockType, float> &blockRarity : blockRarities)
			{
				float chance = blockRarity.second * dice;

				if (roll <= chance)
				{
					switch (blockRarity.first)
					{
						case BlockType::Stone:
							minableTilePartition_.add(new MinableTile(col, row, 100.0f, 2, stoneTexture, digTexture));
							break;
						case BlockType::Coal:
							minableTilePartition_.add(new MinableTile(col, row, 150.0f, 5, coalTexture, digTexture));
							break;
						case BlockType::Copper:
							minableTilePartition_.add(new MinableTile(col, row, 200.0f, 7, copperTexture, digTexture));
							break;
						case BlockType::Iron:
							minableTilePartition_.add(new MinableTile(col, row, 250.0f, 10, ironTexture, digTexture));
							break;
						case BlockType::Gold:
							minableTilePartition_.add(new MinableTile(col, row, 300.0f, 15, goldTexture, digTexture));
							break;
						case BlockType::Ruby:
							minableTilePartition_.add(new MinableTile(col, row, 1000.0f, 100, rubyTexture, digTexture));
							break;
						case BlockType::Emerald:
							minableTilePartition_.add(new MinableTile(col, row, 1000.0f, 125, emeraldTexture, digTexture));
							break;
						case BlockType::Sapphire:
							minableTilePartition_.add(new MinableTile(col, row, 1000.0f, 150, sapphireTexture, digTexture));
							break;
					}
					break;
				}
				else
				{
					roll -= static_cast<int>(chance);
				}
			}
		}
	}
}