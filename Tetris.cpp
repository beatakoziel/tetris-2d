#include "pch.h"
#include <iostream>
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <windows.h>
#include <ctime>

#include "Menu.h"
#include "Game.h"
#include "Tetris.h"
#include "Figure.h"
#include "Board.h"

bool canDrawFigure = true, canMoveHorizontally = true, canMoveFaster = false, canRotate = false, gameOver = false, firstGeneration = true;
const int sumOfSquareSizeAndDistance = 32, sizeOfSquare = 30;
int counter = 0, scorePoints = 0, columns = 12;
Figure currentFigure, nextFigure;
Board board;

int main()
{
	Game game;
	float gameSpeed = 1.f;
	sf::Vector2i screenDimensions(600, 650);
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "THE BEST TETRIS EVER");

	Menu menu((float)window.getSize().x, (float)window.getSize().y);
	sf::Image image;
	if(!image.loadFromFile("resources/imgs/tetris-figure.jpg"))
		sf::err();
	window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

	sf::Texture menuTexture = menu.loadMenuBackground();
	sf::Sprite displayedSprite = menu.createMenuSprite(menuTexture);
	sf::Texture squareTexture = currentFigure.loadFigureTexture();
	sf::Texture gameTexture;
	if (!gameTexture.loadFromFile("resources/imgs/wall.jpg"))
		sf::err();
	sf::Texture gameoverTexture;
		if (!gameoverTexture.loadFromFile("resources/imgs/crying.jpg"))
			sf::err();
	gameoverTexture.setSmooth(true);

	sf::Sprite gameoverSprite;
	gameoverSprite.setColor(sf::Color(167, 167, 163));
	gameoverSprite.setTexture(gameoverTexture);

	sf::Event event;
	sf::Clock timer;

	float differenceX, differenceY;
	
	srand((unsigned)time(NULL));
	setUpNextAndCurrentFigure(window);
	
	sf::Sound enterSound;
	sf::SoundBuffer enterSoundBuffer;

	if (!enterSoundBuffer.loadFromFile("resources/sounds/menu_choice.ogg"))
		std::cout << "cant open menu_choice sound";
	else
		enterSound.setBuffer(enterSoundBuffer);

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
					{
						enterSound.play();
						switch (menu.getPressedItem())
						{
						case 0: //play
							window.clear();
							board = Board(columns, squareTexture);
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
		gameOverGoTo:
		if (!gameOver) 
		{
			menuTexture = game.loadGameBackground();
			displayedSprite = game.createGameSprite(gameTexture, window.getSize().x, window.getSize().y);

			sf::Music gameMusic;
			if (!gameMusic.openFromFile("resources/sounds/game.ogg"))
				std::cout << "cant open game music";
			gameMusic.setLoop(true);
			gameMusic.play();
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
							if (board.leftCollisions(currentFigure) && canMoveHorizontally)
								currentFigure.moveLeft();
							break;
						case sf::Keyboard::Right:
							if (board.rightCollisions(currentFigure) && canMoveHorizontally)
								currentFigure.moveRight();
							break;
						case sf::Keyboard::Down:
							if (canRotate)
								currentFigure.moveRotate(columns, board.getBoardSquare());
							break;
						case sf::Keyboard::Space:
							if (canMoveFaster)
								currentFigure.moveDownFaster(window);
							break;
						case sf::Keyboard::P:
							board.changeColorsOfLines();
							break;
						}
						break;
					}
				}

				window.clear();
				window.draw(displayedSprite);
				board.drawBoard(window);
				if (timer.getElapsedTime() >= sf::seconds(gameSpeed)) {
					scorePoints += board.checkLineOfSquares();
					if (board.isItEndOfTheTetris()) {
						gameMusic.pause();
						gameOver = true;
						goto gameOverGoTo;
					}						
					generateFigure(window, columns);
					timer.restart();
				}

				drawCurrentFigure(squareTexture, window);
				drawNextFigure(differenceX, differenceY, squareTexture, window);
				board.showScore(window, scorePoints, false);

				if (!board.downCollisions(currentFigure))
				{
					if (timer.getElapsedTime() >= sf::seconds(gameSpeed - 0.05f))
					{
						canMoveHorizontally = false;
						canDrawFigure = true;
						board.setPresenceInWholeBoard(currentFigure);
					}
					canRotate = false;
					canMoveFaster = false;
				}
				else {
					canRotate = true;
					canMoveFaster = true;
					canMoveHorizontally = true;
				}
				window.display();
			}
		}
	else {
	window.clear();
	sf::Music endMusic;
	if (!endMusic.openFromFile("resources/sounds/lose.ogg"))
		std::cout << "cant open end music";
	endMusic.play();
			while (window.isOpen()) {
				window.clear();
				while (window.pollEvent(event))
				{
					switch (event.type)
					{
					case sf::Event::Closed:
						window.close();
						break;
					}
				}
				window.draw(gameoverSprite);
				board.showScore(window, scorePoints, true);
				window.display();
			}
	}
	}
	return 0;
}

void generateFigure(sf::RenderWindow &window, int maximumX)
{
	int positionXOfFigure = ((rand() % maximumX) * sumOfSquareSizeAndDistance);
	if (positionXOfFigure == 0)
		positionXOfFigure = 32;
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
				position = Point((float)i * sumOfSquareSizeAndDistance + positionXOfFigure, (float)j * sumOfSquareSizeAndDistance - 96);
				figure.setSquaresCoordinates(whichSquare, position);
				whichSquare++;
				figureSprite.setPosition(position.getX(), position.getY());
			}
		}
		if (firstGeneration)
			nextFigure = figure;
		else
		{
			currentFigure = nextFigure;
			nextFigure = figure;
		}

	}
	else currentFigure.moveDown();

	if (currentFigure.getLastSquaresCoordinates().getY() < 640)
		canDrawFigure = false;
	else {
		canDrawFigure = true;
		if (canMoveHorizontally)
			board.setPresenceInWholeBoard(currentFigure);
	}
}



void drawNextFigure(float &differenceX, float &differenceY, sf::Texture &squareTexture, sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		float squareX = nextFigure.getSquaresCoordinates()[i].getX();
		float squareY = nextFigure.getSquaresCoordinates()[i].getY();
		if (i == 0)
		{
			differenceX = (float)(columns + 3) * 32 - squareX;
			differenceY = 200 - squareY;
		}
		squareX = squareX + differenceX;
		squareY = squareY + differenceY;
		Point position = Point(squareX, squareY);
		sf::Sprite currentSquareSprite;
		currentSquareSprite.setTexture(squareTexture);
		currentSquareSprite.setColor(nextFigure.getColor());
		currentSquareSprite.setPosition(position.getX(), position.getY());
		window.draw(currentSquareSprite);
	}
}

void drawCurrentFigure(sf::Texture &squareTexture, sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		float squareX = currentFigure.getSquaresCoordinates()[i].getX();
		float squareY = currentFigure.getSquaresCoordinates()[i].getY();
		Point position = Point(squareX, squareY);
		sf::Sprite currentSquareSprite;
		currentSquareSprite.setTexture(squareTexture);
		currentSquareSprite.setColor(currentFigure.getColor());
		currentSquareSprite.setPosition(position.getX(), position.getY());
		window.draw(currentSquareSprite);
	}
}

void setUpNextAndCurrentFigure(sf::RenderWindow &window)
{
	generateFigure(window, columns);
	firstGeneration = false;
	canDrawFigure = true;
	generateFigure(window, columns);
	canDrawFigure = true;
	generateFigure(window, columns);
}
