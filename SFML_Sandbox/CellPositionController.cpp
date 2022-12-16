#include "CellPositionController.h"

CellPositionController::CellPositionController(World* _world, Cell _cell) {
	cell = _cell;
	world = _world;
	setPositions();

};

void CellPositionController::fallDownLeftRight() {
	// Check if down is a possible move and empty
	if (world->isInsideBoundsAndEmpty(positions["DOWN"])) {
		// If down is empty, go down
		world->move(cell, positions["DOWN"]);
	}
	// Check if down-left and down-right are possible moves and are empty
	else if (world->isInsideBoundsAndEmpty({ positions["DOWN_LEFT"], positions["DOWN_RIGHT"] })) {
		float randomValue = (float)rand() / RAND_MAX;

		// Random decition to go left or right
		if (randomValue < 0.5) {
			world->move(cell, positions["DOWN_LEFT"]);
		}
		else {
			world->move(cell, positions["DOWN_RIGHT"]);
		}
	}
	else if (world->isInsideBoundsAndEmpty(positions["DOWN_LEFT"])) {
		world->move(cell, positions["DOWN_LEFT"]);
	}
	else if (world->isInsideBoundsAndEmpty(positions["DOWN_RIGHT"])) {
		world->move(cell, positions["DOWN_RIGHT"]);
	}
};

void CellPositionController::setPositions() {
	positions = std::unordered_map<std::string, Position>{
		{"TOP_LEFT", {cell.position.x - 1, cell.position.y - 1}},
		{"TOP", {cell.position.x, cell.position.y - 1}},
		{"TOP_RIGHT", {cell.position.x + 1, cell.position.y - 1}},

		{"LEFT", {cell.position.x - 1, cell.position.y}},
		{"RIGHT", {cell.position.x + 1, cell.position.y}},

		{"DOWN_LEFT", {cell.position.x - 1, cell.position.y + 1}},
		{"DOWN", {cell.position.x, cell.position.y + 1}},
		{"DOWN_RIGHT", {cell.position.x + 1, cell.position.y + 1}},
	};
};