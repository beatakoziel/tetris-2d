#include "pch.h"
#include <iostream>
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"

#include "Menu.h"
#include "Game.h"
#include "Tetris.h"
#include "Figure.h"

int main()
{
	Game game;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "THE BEST TETRIS EVER");

	Menu menu((float)window.getSize().x, (float)window.getSize().y);
	window.setFramerateLimit(15);
	//window.setIcon("tetris-figure.jpg");

	sf::Texture background_texture = menu.loadMenuBackground();
	sf::Sprite displayedSprite = menu.createMenuSprite(background_texture);
	
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
						//figure.moveLeft();
						break;
					case sf::Keyboard::Right:
						//figure.moveRight();
						break;
					case sf::Keyboard::Space:
						//figure.moveFaster();
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
			drawFigure(window);
			window.display();
		}
	}
	return 0;
}

void drawFigure( sf::RenderWindow &window)
{
	Figure figure;
	int** figureMatrix = figure.getFigureMatrix();
	sf::Sprite figureSprite = figure.getFigureSprite();
	int whichSquare = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (figureMatrix[i][j] == 0) continue;
			figureSprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
			Point position = Point(i * 32, j * 32);
			figure.setSquaresPosition(whichSquare, position);
			whichSquare++;
			figureSprite.setPosition(position.getX(), position.getY());
			window.draw(figureSprite);
		}
	}
	figure.moveDown();
}

