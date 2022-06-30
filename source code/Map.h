#pragma once

class TextureData;
class ParticlePool;

#include "GridPartition.h"
#include "MinableTile.h"
#include <SFML/Graphics/Drawable.hpp>

class Map : public sf::Drawable
{
public:
	Map(uint16_t numCols, uint16_t numRows, const TextureData &textureData, ParticlePool &particlePool);
	~Map() {}

	void dig(int col, int row, float damage);

	void updateVisibility(int playerMapCol, int playerMapRow);
	void forceUpdateVisibility(int playerMapCol, int playerMapRow);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool existsMinableTile(int col, int row) const;
	bool isInBounds(int col, int row) const;
	float getWidth() const;
	float getHeight() const;
private:
	const TextureData &textureData_;
	ParticlePool &particlePool_;

	GridPartition<MinableTile> minableTilePartition_;
	std::vector<MinableTile *> visibleMinableTiles_;

	GridPartition<Tile> scenicTilePartition_;
	std::vector<Tile *> visibleScenicTiles_;

	Coords gridPartitionCoords_;

	uint16_t numCols_;
	uint16_t numRows_;

	void generate_();
};