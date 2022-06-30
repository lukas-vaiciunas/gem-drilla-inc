#include "Coords.h"

Coords::Coords(int col, int row) :
	col_(col),
	row_(row)
{}

bool Coords::operator==(const Coords &other) const
{
	return col_ == other.col_ && row_ == other.row_;
}

bool Coords::operator!=(const Coords &other) const
{
	return !this->operator==(other);
}

int Coords::getCol() const
{
	return col_;
}

int Coords::getRow() const
{
	return row_;
}