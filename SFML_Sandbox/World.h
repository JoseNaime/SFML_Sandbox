#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>

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

	bool isInsideBounds(int, int);

};

#endif