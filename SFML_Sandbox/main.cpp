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
	int count = 0;

	static bool pressed;
	static sf::Mouse::Button buttonPressed;

	// run the program as long as the window is open
	while (window.isOpen()) {

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				std::cout << "Mouse Button Pressed" << std::endl;
				pressed = true;
				if (event.mouseButton.button == sf::Mouse::Left) {
					buttonPressed = sf::Mouse::Left;
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					buttonPressed = sf::Mouse::Right;
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				pressed = false;
				std::cout << "Mouse Button Release" << std::endl;
			}
		}

		if (pressed) {

			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

			int gridX = floor(mousePosition.x / world.getCellSize());
			int gridY = floor(mousePosition.y / world.getCellSize());

			if (buttonPressed == sf::Mouse::Left) {
				world.spawnElement(Cell(CELL_TYPE::SAND, { gridX, gridY }));
			}
			else if (buttonPressed == sf::Mouse::Right) {
				world.deleteElement({ gridX, gridY });
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