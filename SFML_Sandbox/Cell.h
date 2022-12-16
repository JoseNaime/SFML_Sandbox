#ifndef CELL_H
#define CELL_H

#include <vector>

struct Position {
	int x;
	int y;
};

enum class ELEMENT_PROPERTY {
	SOLID,
	LIQUID,
	GAS
};

enum class CELL_TYPE {
	EMPTY = 0,
	SAND = 1,
	WATER = 2,
};

class Cell {
public:
	Cell();
	Cell(CELL_TYPE _type, Position _position);
	void assignProperties();


	CELL_TYPE type;
	Position position;
	std::vector<ELEMENT_PROPERTY> properties = {};
};

#endif