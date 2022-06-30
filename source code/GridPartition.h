#pragma once

#include "GridPartitionCell.h"
#include "Coords.h"

template<typename T>
class GridPartition
{
public:
	GridPartition(uint16_t numCols, uint16_t numRows, uint8_t cellSize);

	void add(T *object);
	void remove(int mapCol, int mapRow);

	bool existsObject(int mapCol, int mapRow) const;
	T &getObjectRef(int mapCol, int mapRow);
	const T &getObject(int mapCol, int mapRow) const;
	std::vector<T *> getObjectsNear(int mapCol, int mapRow) const;
	std::vector<T *> getObjectsNear(const Coords &cellCoords) const;
	Coords getCellCoords(int mapCol, int mapRow) const;
private:
	std::vector<std::vector<GridPartitionCell<T>>> cells_;
	uint16_t numCols_;
	uint16_t numRows_;
	uint8_t cellSize_;

	void appendIfValid(std::vector<T *> &lhs, int cellCol, int cellRow) const;
};

template<typename T>
GridPartition<T>::GridPartition(uint16_t numCols, uint16_t numRows, uint8_t cellSize) :
	cells_(numRows, std::vector<GridPartitionCell<T>>(numCols, GridPartitionCell<T>(cellSize))),
	numCols_(numCols),
	numRows_(numRows),
	cellSize_(cellSize)
{}

template<typename T>
void GridPartition<T>::add(T *object)
{
	Coords cellCoords = std::move(this->getCellCoords(object->getMapCol(), object->getMapRow()));

	cells_[cellCoords.getRow()][cellCoords.getCol()].add(
		object,
		object->getMapCol() - cellCoords.getCol() * cellSize_,
		object->getMapRow() - cellCoords.getRow() * cellSize_);
}

template<typename T>
void GridPartition<T>::remove(int mapCol, int mapRow)
{
	Coords cellCoords = std::move(this->getCellCoords(mapCol, mapRow));

	cells_[cellCoords.getRow()][cellCoords.getCol()].remove(
		mapCol - cellCoords.getCol() * cellSize_,
		mapRow - cellCoords.getRow() * cellSize_);
}

template<typename T>
T &GridPartition<T>::getObjectRef(int mapCol, int mapRow)
{
	Coords cellCoords = std::move(this->getCellCoords(mapCol, mapRow));

	return cells_[cellCoords.getRow()][cellCoords.getCol()].getObjectRef(
		mapCol - cellCoords.getCol() * cellSize_,
		mapRow - cellCoords.getRow() * cellSize_);
}

template<typename T>
const T &GridPartition<T>::getObject(int mapCol, int mapRow) const
{
	Coords cellCoords = std::move(this->getCellCoords(mapCol, mapRow));

	return cells_[cellCoords.getRow()][cellCoords.getCol()].getObject(
		mapCol - cellCoords.getCol() * cellSize_,
		mapRow - cellCoords.getRow() * cellSize_);
}

template<typename T>
bool GridPartition<T>::existsObject(int mapCol, int mapRow) const
{
	Coords cellCoords = std::move(this->getCellCoords(mapCol, mapRow));

	return cells_[cellCoords.getRow()][cellCoords.getCol()].existsObject(
		mapCol - cellCoords.getCol() * cellSize_,
		mapRow - cellCoords.getRow() * cellSize_);
}

template<typename T>
std::vector<T *> GridPartition<T>::getObjectsNear(int mapCol, int mapRow) const
{
	Coords cellCoords = std::move(this->getCellCoords(mapCol, mapRow));

	return this->getTilesNear(cellCoords);
}

template<typename T>
std::vector<T *> GridPartition<T>::getObjectsNear(const Coords &cellCoords) const
{
	int cellCol = cellCoords.getCol();
	int cellRow = cellCoords.getRow();

	std::vector<T *> objectsNear;

	this->appendIfValid(objectsNear, cellCol - 1, cellRow - 1);
	this->appendIfValid(objectsNear, cellCol, cellRow - 1);
	this->appendIfValid(objectsNear, cellCol + 1, cellRow - 1);
	this->appendIfValid(objectsNear, cellCol - 1, cellRow);
	this->appendIfValid(objectsNear, cellCol, cellRow);
	this->appendIfValid(objectsNear, cellCol + 1, cellRow);
	this->appendIfValid(objectsNear, cellCol - 1, cellRow + 1);
	this->appendIfValid(objectsNear, cellCol, cellRow + 1);
	this->appendIfValid(objectsNear, cellCol + 1, cellRow + 1);

	return objectsNear;
}

template<typename T>
Coords GridPartition<T>::getCellCoords(int mapCol, int mapRow) const
{
	float cellSizeRatio = 1.0f / cellSize_;

	return Coords(static_cast<int>(mapCol * cellSizeRatio), static_cast<int>(mapRow * cellSizeRatio));
}

template<typename T>
void GridPartition<T>::appendIfValid(std::vector<T *> &lhs, int cellCol, int cellRow) const
{
	if (cellCol < 0 || cellRow < 0 || cellCol >= numCols_ || cellRow >= numRows_) return;

	const std::vector<std::vector<T *>> &objects = cells_[cellRow][cellCol].getObjects();

	for (uint8_t row = 0; row < cellSize_; ++row)
	{
		for (uint8_t col = 0; col < cellSize_; ++col)
		{
			if (objects[row][col] != nullptr)
				lhs.push_back(objects[row][col]);
		}
	}
}