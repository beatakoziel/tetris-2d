#include "pch.h"
#include <iostream>
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <windows.h>
#include <ctime>

#include "Menu.h"
#include "Game.h"
#include "Tetris.h"
#include "Figure.h"
#include "Board.h"

bool canDrawFigure = true;
Figure currentFigure;
int counter = 0;

int main()
{
	Game game;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "THE BEST TETRIS EVER");

	Menu menu((float)window.getSize().x, (float)window.getSize().y);
	//window.setFramerateLimit(15);
	//window.setIcon("tetris-figure.jpg");

	sf::Texture background_texture = menu.loadMenuBackground();
	sf::Sprite displayedSprite = menu.createMenuSprite(background_texture);
	sf::Texture squareTexture = currentFigure.loadFigureTexture();

	sf::Event event;
	sf::Clock timer;
	Board board;
	/*sf::Clock clock;
	sf::Time time;*/
	srand((unsigned)time(NULL));

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
							board = Board(10, squareTexture);
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
						currentFigure.moveLeft(window);
						break;
					case sf::Keyboard::Right:
						currentFigure.moveRight(window);
						break;
					case sf::Keyboard::Space:
						currentFigure.moveDownFaster(window);
						break;
					}
					break;
				}
			}

			window.clear();
			//window.draw(displayedSprite);
			board.drawBoard(window);

			if (timer.getElapsedTime() >= sf::seconds(1.0f)) {
				drawFigure(window);
				timer.restart();
			}

			for (int i = 0; i < 4; i++)
			{
				float squareX = currentFigure.getSquaresCoordinates()[i].getX();
				float squareY = currentFigure.getSquaresCoordinates()[i].getY();
				Point position = Point(squareX, squareY); //DAC DO J -96
				sf::Sprite currentSquareSprite;
				currentSquareSprite.setTexture(squareTexture);
				currentSquareSprite.setColor(currentFigure.getColor());
				currentSquareSprite.setPosition(position.getX(), position.getY());
				window.draw(currentSquareSprite);
			}
			
			window.display();
		}
	}
	return 0;
}

void drawFigure(sf::RenderWindow &window)
{
	const int maximumX = 16;
	const int sumOfSquareSizeAndDistance = 32;
	const int sizeOfSquare = 30;
	int positionXOfFigure = (1 + rand() % maximumX) * sumOfSquareSizeAndDistance;
	Figure figure;
	int** figureMatrix;
	sf::Sprite figureSprite;
	int whichSquare = 0;
	Point position;
	if (canDrawFigure == true) {
		figureMatrix = figure.getFigureMatrix();
		figureSprite = figure.getFigureSprite();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (figureMatrix[i][j] == 0)
					continue;
				figureSprite.setTextureRect(sf::IntRect(0, 0, sizeOfSquare, sizeOfSquare));
				position = Point(i * sumOfSquareSizeAndDistance + positionXOfFigure, j * sumOfSquareSizeAndDistance -96); 
				figure.setSquaresCoordinates(whichSquare, position);
				std::cout << "x: " << figure.getLastSquaresCoordinates().getX() << "\n";
				std::cout << "y: " << figure.getLastSquaresCoordinates().getY() << "\n";
				whichSquare++;
				figureSprite.setPosition(position.getX(), position.getY());
				window.draw(figureSprite);
			}
		}
		currentFigure = figure;
	}
	else {
		figure = currentFigure;
		figure.moveDown(window);
	}
	if (figure.getLastSquaresCoordinates().getY() < 640)
		canDrawFigure = false;
	else canDrawFigure = true;
	currentFigure = figure;
}

