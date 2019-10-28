#include "pch.h"
#include <iostream>
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"

#include "Menu.h"
#include "Game.h"

int main()
{
	Game game;

	sf::RenderWindow window(sf::VideoMode(800, 600), "The best Tetris ever");

	Menu menu((float)window.getSize().x, (float)window.getSize().y);
	window.setFramerateLimit(15);

	sf::Texture background_texture = menu.loadMenuBackground();
	sf::Sprite displayedSprite = menu.createMenuSprite(background_texture);

	sf::Texture tetris_figure_texture = game.loadTetrisFigureTexture();
	sf::Sprite tetris_figure = game.createFigureSprite(tetris_figure_texture);
	

	sf::Event event;
	sf::Clock clock;
	sf::Time time;

	refreshGame:
	if (menu.visible == true) {
		while (window.isOpen())
		{
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
							case 0: //play
								window.clear();
								menu.visible = false;
								goto refreshGame;
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

			window.draw(displayedSprite);
			menu.drawTextInMenu(window);

			window.display();
		}
	}
	else {
		background_texture = game.loadGameBackground();
		displayedSprite = game.createGameSprite(background_texture, window.getSize().x, window.getSize().y);

		int **figure;

		while (window.isOpen()) {
			
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
					case sf::Keyboard::Left:
						game.moveLeft();
						break;
					case sf::Keyboard::Right:
						game.moveRight();
						break;
					case sf::Keyboard::Space:

						break;

					case sf::Keyboard::LControl || sf::Keyboard::RControl:
						
						break;
					}
					break;
				}				
			}

			/*time = clock.getElapsedTime(); //time.asSeconds(); 
			clock.restart().asSeconds();*/
			//game.generateTetrisFigure();

			window.clear();
			window.draw(displayedSprite);

			/*window.draw(tetris_figure);

			window.display();*/
			figure = game.generateTetrisFigure();

			tetris_figure.setColor(game.generateColorOfTetrisFigure());

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (figure[i][j] == 0) continue;
					tetris_figure.setTextureRect(sf::IntRect(0, 0, 30, 30));
					tetris_figure.setPosition(i*32, j*32);
					window.draw(tetris_figure);
				}	
			}
			window.display();
		}
	}
	return 0;
}

