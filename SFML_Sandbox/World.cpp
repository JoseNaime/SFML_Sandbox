#include "World.h"

World::World(unsigned int _width, unsigned int _height) {
	width = floor(_width / elementSize) + 1 ;
	height = floor(_height / elementSize) + 1;

	// Init grid with empty cells 0
	for (unsigned int i = 0; i < width - 1 ; i++) {
		std::vector<int> line = {};
		for (unsigned int j = 0; j < height - 1; j++) {
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
	for (unsigned int i = 0; i < width - 1; i++) {
		for (unsigned int j = 0; j < height - 1; j++) {
			int cell_type = previousGrid[i][j];

			if (cell_type == 0) continue;

			switch (cell_type) {
				case 1:

					if (isInsideBounds(i, j + 1) && previousGrid[i][j + 1] == 0) {
						grid[i][j] = 0;
						grid[i][j + 1] = cell_type;
					}

					break;

				default:
					break;
			}
		}
	}
}

void World::draw(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < width - 1; i++) {
		for (unsigned int j = 0; j < height - 1; j++) {
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

void World::spawnElement(int x, int y, int elementId) {
	if (!isInsideBounds(x, y)) return;

	grid[x][y] = elementId;
}

int World::getElementSize() {
	return elementSize;
}