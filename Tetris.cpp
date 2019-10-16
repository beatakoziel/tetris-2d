#include "pch.h"
#include <iostream>
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"

#include "Menu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
					window.close();
					break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.moveUp();
					break;

				case sf::Keyboard::Down:
					menu.moveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.getPressedItem())
					{
					case 0:
						//play
						break;
					case 1:
						//options
						break;
					case 2:
						window.close();
						break;
					}
				}
					break;
			}
		}

		window.clear();

		menu.draw(window);

		window.display();
	}
	return 0;
}
