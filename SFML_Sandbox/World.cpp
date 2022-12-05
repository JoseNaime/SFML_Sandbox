#include "World.h"

World::World(unsigned int _width, unsigned int _height) {
	width = floor(_width / elementSize);
	height = floor(_height / elementSize);

	// Init grid with empty cells 0
	for (unsigned int i = 0; i < width; i++) {
		std::vector<int> line = {};
		for (unsigned int j = 0; j < height; j++) {
			line.push_back(0);
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
			int cell_type = previousGrid[i][j];

			// If cell is empty, continue
			if (cell_type == 0) continue;


			Element currElement = {
				cell_type, // type int
				Position{i, j} // position Position{ x, y}
			};

			std::array<int, 2> DOWN = {
				currElement.position.x ,
				currElement.position.y + 1
			};

			std::array<int, 2> DOWN_LEFT = {
				currElement.position.x - 1,
				currElement.position.y + 1
			};

			std::array<int, 2> DOWN_RIGHT = {
				currElement.position.x + 1 ,
				currElement.position.y + 1
			};


			switch (cell_type) {
				case 1:

					// Check if down is a possible move and empty
					if (isInsideBoundsAndEmpty(&DOWN)) {
						// If down is empty, go down
						grid[i][j] = 0;
						grid[i][j + 1] = cell_type;
					}


					// Check if down-left and down-right are possible moves and are empty
					else if (isInsideBoundsAndEmpty({ &DOWN_LEFT, &DOWN_RIGHT })) {
						grid[i][j] = 0;
						grid[i - 1][j + 1] = cell_type;
					}
					else if (isInsideBoundsAndEmpty(&DOWN_LEFT)) {
						grid[i][j] = 0;
						grid[i - 1][j + 1] = cell_type;
					}
					else if (isInsideBoundsAndEmpty(&DOWN_RIGHT)) {
						grid[i][j] = 0;
						grid[i + 1][j + 1] = cell_type;
					}

					//break;

				default:
					break;
			}
		}
	}
}

void World::draw(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			int cell_type = grid[i][j];

			// Check if current cell is an empty space, if so, continue
			if (cell_type != 0) {

				// Generate rectangle
				sf::RectangleShape shape = sf::RectangleShape();

				shape.setSize(sf::Vector2f(elementSize, elementSize));
				shape.setPosition(i * elementSize, j * elementSize);

				switch (cell_type) {

					case 1:
						shape.setFillColor(sf::Color::White);
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

bool World::isInsideBounds(int x, int y) {
	return (x > 0 && y > 0) &&  // Check if its not less than 0
		(x < width&& y < height); // Check if it is not over width or height
}

bool World::isInsideBoundsAndEmpty(std::array<int, 2>* arrayReference) {
	std::array<int, 2> position = *arrayReference;
	int _x = position[0];
	int _y = position[1];

	return (isInsideBounds(_x, _y) && previousGrid[_x][_y] == 0);
}

bool World::isInsideBoundsAndEmpty(std::vector<std::array<int, 2>* > vectorOfPositions) {
	if (vectorOfPositions.size() == 0) {
		std::wcerr << "isInsideBoundsAndEmpty can't recieve an empty vector of positions, returning false" << std::endl;
		return false;
	}
	if (vectorOfPositions.size() == 1) {
		std::wcerr << "For checking just 1 position, replace with isInsideBoundsAndEmpty( _x, _y) rather than using a vector" << std::endl;
	}

	for (int i = 0; i < vectorOfPositions.size(); i++) {
		std::array<int, 2> currentPosition = *vectorOfPositions[i];
		int _x = currentPosition[0];
		int _y = currentPosition[1];

		if (!(isInsideBounds(_x, _y) && previousGrid[_x][_y] == 0)) {
			return false;
		}
	}

	return true;
}

void moveElement(std::array<int, 2>* arrayReference) {
	std::array<int, 2> position = *arrayReference;

}

void World::spawnElement(int x, int y, int elementId) {
	if (!isInsideBounds(x, y)) return;

	grid[x][y] = elementId;
}

int World::getElementSize() {
	return elementSize;
}