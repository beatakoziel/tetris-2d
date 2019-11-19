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

bool canDrawFigure = true, canMoveHorizontally = true, canMoveFaster = false, canRotate = false, gameOver = false;
Figure currentFigure;
Figure nextFigure;
boolean firstGeneration = true;
int counter = 0, scorePoints = 0, columns = 12;
Board board;


void generateFigure(sf::RenderWindow &window, int maximumX)
{
	const int sumOfSquareSizeAndDistance = 32;
	const int sizeOfSquare = 30;
	int positionXOfFigure = ((rand() % maximumX ) * sumOfSquareSizeAndDistance);
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
		{
			nextFigure = figure;
		}
		else
		{
			currentFigure = nextFigure;
			nextFigure = figure;
		}

	}
	else currentFigure.moveDown();

	if (currentFigure.getLastSquaresCoordinates().getY()< 640)
		canDrawFigure = false;
	else {
		canDrawFigure = true;
		if(canMoveHorizontally)
			board.setPresenceInWholeBoard(currentFigure);
	}
	std::cout << "generowanie figury\n";
}



int main()
{
	Game game;
	float gameSpeed = 1.f;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "THE BEST TETRIS EVER");

	Menu menu((float)window.getSize().x, (float)window.getSize().y);
	//window.setFramerateLimit(15);
	//window.setIcon("tetris-figure.jpg");

	sf::Texture background_texture = menu.loadMenuBackground();
	sf::Sprite displayedSprite = menu.createMenuSprite(background_texture);
	sf::Texture squareTexture = currentFigure.loadFigureTexture();
	sf::Texture gameover_texture;
		if (!gameover_texture.loadFromFile("resources/imgs/game-over.png"))
			sf::err();
	gameover_texture.setSmooth(true);

	sf::Sprite gameoverSprite;
	gameoverSprite.setTexture(gameover_texture);

	sf::Event event;
	sf::Clock timer;

	float differenceX;
	float differenceY;
	
	/*sf::Clock clock;
	sf::Time time;*/
	srand((unsigned)time(NULL));
	generateFigure(window, columns);
	firstGeneration = false;
	canDrawFigure = true;
	generateFigure(window, columns);
	canDrawFigure = true;
	generateFigure(window, columns);
	
	sf::Music music;
	if (!music.openFromFile("resources/sounds/menu.ogg"))
		std::cout << "cant open menu music";
	music.setVolume(80.f);
	music.play();

	sf::Sound enterSound;
	sf::SoundBuffer soundBuffer1;
	if (!soundBuffer1.loadFromFile("resources/sounds/menu_choice.ogg"))
		std::cout << "cant open menu_choice sound";
	else
		enterSound.setBuffer(soundBuffer1);

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
						music.pause();
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
			background_texture = game.loadGameBackground();
			displayedSprite = game.createGameSprite(background_texture, window.getSize().x, window.getSize().y);

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
							//if (board.rightCollisions(currentFigure) && canMoveHorizontally)
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
				board.showScore(window, scorePoints);

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
				window.display();
			}
	}
	}
	return 0;
}
