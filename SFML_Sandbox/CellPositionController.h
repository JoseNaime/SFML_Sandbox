#ifndef CELL_POSITION_CONTROLLER_H
#define CELL_POSITION_CONTROLLER_H

#include "Cell.h"
#include "World.h"
#include "unordered_map"

class World;

class CellPositionController {
public:
	CellPositionController(World* ,Cell );
	void fallDownLeftRight();
	void setPositions();

private:
	Cell cell;
	World* world;
	std::unordered_map<std::string, Position> positions;


};

#endif // !CELL_POSITION_CONTROLLER_H




