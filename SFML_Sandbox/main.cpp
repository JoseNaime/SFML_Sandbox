#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "World.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My first window");

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(120);

    World world(SCREEN_WIDTH, SCREEN_HEIGHT);
    

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                int gridX = floor(mousePosition.x / world.getCellSize());
                int gridY = floor(mousePosition.y / world.getCellSize());

                world.spawnElement(Cell(CELL_TYPE::SAND, { gridX, gridY }));
 
            }
        }

        // Logic update
        world.update();

        // Clear the window
        window.clear(sf::Color::Black);

        // Start Draw
        world.draw(window);

        // End Current Frame
        window.display();

    }

	return 0;
}