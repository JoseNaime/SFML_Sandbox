#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <iostream>
#include <random>
#include "CellPositionController.h"
#include "Cell.h"

class World {
public:
	World(unsigned int, unsigned int);
	~World();
	void update();
	void draw(sf::RenderWindow &);
	void spawnElement(Cell);
	void deleteElement(Position);
	int getCellSize();

	bool isInsideBounds(Position);
	bool isInsideBoundsAndEmpty(Position);
	bool isInsideBoundsAndEmpty(std::vector< Position >);

	void move(Cell, Position);

	const unsigned int cellSize = 8;
	unsigned int width, height;
	std::vector< std::vector<Cell> > grid;
	std::vector< std::vector<Cell> > previousGrid;

};

#endif