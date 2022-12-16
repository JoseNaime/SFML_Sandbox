#include "Cell.h"

Cell::Cell() {

};

Cell::Cell(CELL_TYPE _type, Position _position) {
	type = _type;
	position = _position;

	assignProperties();
};

void Cell::assignProperties() {
	switch (type) {
		case CELL_TYPE::EMPTY:
			break;
		case CELL_TYPE::SAND:
			properties = std::vector<ELEMENT_PROPERTY>{ ELEMENT_PROPERTY::SOLID };
			break;
		case CELL_TYPE::WATER:
			properties = std::vector<ELEMENT_PROPERTY>{ ELEMENT_PROPERTY::LIQUID };
			break;
		default:
			break;
	}
};