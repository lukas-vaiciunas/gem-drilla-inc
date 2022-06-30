#pragma once

class Coords
{
public:
	Coords(int col, int row);

	bool operator==(const Coords &other) const;
	bool operator!=(const Coords &other) const;

	int getCol() const;
	int getRow() const;
private:
	int col_;
	int row_;
};