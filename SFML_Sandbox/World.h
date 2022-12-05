#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <iostream>

struct Position {
	int x;
	int y;
};

struct Element {
	int type; // TODO: Replace with an enum
	Position position;
};

class World {
public:
	World(unsigned int, unsigned int);
	~World();
	void update();
	void draw(sf::RenderWindow &);
	void spawnElement(int x, int y, int elementId);
	int getElementSize();

private:
	const unsigned int elementSize = 5;
	unsigned int width, height;
	std::vector< std::vector<int> > grid;
	std::vector< std::vector<int> > previousGrid;

	void moveElement(Position*);

	bool isInsideBounds(int, int);
	bool isInsideBoundsAndEmpty(Position*);
	bool isInsideBoundsAndEmpty(std::vector< Position* >);

};

#endif