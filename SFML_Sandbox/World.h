#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <iostream>
#include <random>


enum class CELL_TYPE {
	EMPTY = 0,
	SAND = 1,
};

struct Position {
	int x;
	int y;
};

struct Cell {
	CELL_TYPE type; 
	Position position;

	Cell(CELL_TYPE _type, Position _position) {
		type = _type;
		position = _position;
	}
};

class World {
public:
	World(unsigned int, unsigned int);
	~World();
	void update();
	void draw(sf::RenderWindow &);
	void spawnElement(Cell);
	void deleteElement(Position);
	int getCellSize();

private:
	const unsigned int cellSize = 8;
	unsigned int width, height;
	std::vector< std::vector<Cell> > grid;
	std::vector< std::vector<Cell> > previousGrid;

	void move(Cell, Position);

	bool isInsideBounds(Position);
	bool isInsideBoundsAndEmpty(Position);
	bool isInsideBoundsAndEmpty(std::vector< Position >);

};

#endif