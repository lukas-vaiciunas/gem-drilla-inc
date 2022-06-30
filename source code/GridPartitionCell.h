#pragma once

#include <vector>

template<typename T>
class GridPartitionCell
{
public:
	GridPartitionCell(uint8_t size);
	~GridPartitionCell();

	void add(T *object, uint8_t col, uint8_t row);
	void remove(uint8_t col, uint8_t row);

	bool existsObject(uint8_t col, uint8_t row) const;
	T &getObjectRef(uint8_t col, uint8_t row);
	const T &getObject(uint8_t col, uint8_t row) const;
	const std::vector<std::vector<T *>> &getObjects() const;
private:
	std::vector<std::vector<T *>> objects_;
	uint8_t size_;
};

template<typename T>
GridPartitionCell<T>::GridPartitionCell(uint8_t size) :
	objects_(size, std::vector<T *>(size, nullptr)),
	size_(size)
{}

template<typename T>
GridPartitionCell<T>::~GridPartitionCell()
{
	for (uint8_t row = 0; row < size_; ++row)
	{
		for (uint8_t col = 0; col < size_; ++col)
		{
			delete objects_[row][col];
		}
	}
}

template<typename T>
void GridPartitionCell<T>::add(T *object, uint8_t col, uint8_t row)
{
	objects_[row][col] = object;
}

template<typename T>
void GridPartitionCell<T>::remove(uint8_t col, uint8_t row)
{
	delete objects_[row][col];
	objects_[row][col] = nullptr;
}

template<typename T>
bool GridPartitionCell<T>::existsObject(uint8_t col, uint8_t row) const
{
	return objects_[row][col] != nullptr;
}

template<typename T>
T &GridPartitionCell<T>::getObjectRef(uint8_t col, uint8_t row)
{
	return *objects_[row][col];
}

template<typename T>
const T &GridPartitionCell<T>::getObject(uint8_t col, uint8_t row) const
{
	return *objects_[row][col];
}

template<typename T>
const std::vector<std::vector<T *>> &GridPartitionCell<T>::getObjects() const
{
	return objects_;
}