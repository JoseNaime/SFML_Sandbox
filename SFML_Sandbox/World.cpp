#include "World.h"

World::World(unsigned int _width, unsigned int _height) {
	width = floor(_width / cellSize);
	height = floor(_height / cellSize);

	// Init grid with empty cells 0
	for (int i = 0; i < width; i++) {
		std::vector<Cell> line = {};
		for (int j = 0; j < height; j++) {
			line.push_back(Cell(CELL_TYPE::EMPTY, { i,j }));
		}
		grid.push_back(line);
	}

	// Copy grid of empty cells to previousGrid
	previousGrid = grid;
}

World::~World() {

}

void World::update() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Cell currentCell = previousGrid[i][j];

			// If cell is empty, continue
			if (currentCell.type == CELL_TYPE::EMPTY) continue;

			CellPositionController cellPositionController(this, currentCell);

			if (std::find(currentCell.properties.begin(), currentCell.properties.end(), ELEMENT_PROPERTY::SOLID) != currentCell.properties.end()) {
				cellPositionController.fallDownLeftRight();
			}

		}
	}
}

void World::draw(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			Cell currentCell = grid[i][j];

			// Check if current cell is an empty space, if so, continue
			if (currentCell.type != CELL_TYPE::EMPTY) {

				// Generate rectangle
				sf::RectangleShape shape = sf::RectangleShape();

				shape.setSize(sf::Vector2f(cellSize, cellSize));
				shape.setPosition(currentCell.position.x * cellSize, currentCell.position.y * cellSize);

				switch (currentCell.type) {

					case CELL_TYPE::SAND:
						shape.setFillColor(sf::Color(168, 127, 50));
						break;

					default:
						break;
				}
				window.draw(shape);
			}
			previousGrid[i][j] = grid[i][j];
		}
	}
}

bool World::isInsideBounds(Position position) {
	return (position.x > 0 && position.y > 0) &&  // Check if its not less than 0
		(position.x < width && position.y < height); // Check if it is not over width or height
}

bool World::isInsideBoundsAndEmpty(Position position) {
	return (isInsideBounds(position) && previousGrid[position.x][position.y].type == CELL_TYPE::EMPTY);
}

bool World::isInsideBoundsAndEmpty(std::vector<Position > vectorOfPositions) {
	if (vectorOfPositions.size() == 0) {
		std::wcerr << "isInsideBoundsAndEmpty can't recieve an empty vector of positions, returning false" << std::endl;
		return false;
	}
	if (vectorOfPositions.size() == 1) {
		std::wcerr << "For checking just 1 position, replace with isInsideBoundsAndEmpty( _x, _y) rather than using a vector" << std::endl;
	}

	for (int i = 0; i < vectorOfPositions.size(); i++) {
		Position position = vectorOfPositions[i];

		if (!(isInsideBounds(position) && previousGrid[position.x][position.y].type == CELL_TYPE::EMPTY)) {
			return false;
		}
	}

	return true;
}

void World::move(Cell cell, Position toPosition) {
	int cell_x = cell.position.x;
	int cell_y = cell.position.y;

	int toPosition_x = toPosition.x;
	int toPosition_y = toPosition.y;

	// Reset current cell posistion cell to 0 (Empty)
	grid[cell_x][cell_y] = Cell(CELL_TYPE::EMPTY, cell.position);

	// Set grid toPosition equals to the cell type
	cell.position = toPosition;
	grid[toPosition_x][toPosition_y] = cell;

}

void World::spawnElement(Cell _cell) {
	if (!isInsideBounds(_cell.position)) return;

	grid[_cell.position.x][_cell.position.y] = _cell;
}

void World::deleteElement(Position position) {
	if (!isInsideBounds(position)) return;

	grid[position.x][position.y] = Cell(CELL_TYPE::EMPTY, position);
}

int World::getCellSize() {
	return cellSize;
}