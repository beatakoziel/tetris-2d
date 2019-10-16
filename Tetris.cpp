#include "pch.h"
#include <iostream>
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"

#include "Menu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");

	Menu menu((float)window.getSize().x, (float)window.getSize().y);

	sf::Texture background_menu = menu.loadMenuBackground();
	sf::Sprite menuSprite = menu.createMenuSprite(background_menu);

	if (menu.visible == true) {
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

			window.draw(menuSprite);
			menu.drawTextInMenu(window);

			window.display();
		}
	}
	return 0;
}

