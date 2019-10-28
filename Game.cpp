#include "pch.h"
#include "Game.h"
#include <time.h>
#include <iostream>

Game::Game()
{
}


Game::~Game()
{
}

sf::Texture Game::loadGameBackground()
{
	sf::Texture background_game;
	if (!background_game.loadFromFile("resources/imgs/game-background.jpg"))
		sf::err();

	return background_game;
}

sf::Sprite Game::createGameSprite(sf::Texture & background_game, int xScreenDimension, int yScreenDimension)
{
	sf::Vector2i screenDimensions(xScreenDimension, yScreenDimension);
	sf::Sprite gameSprite;
	gameSprite.setTexture(background_game);
	gameSprite.setScale(1.0f, (float)screenDimensions.y / background_game.getSize().y);

	return gameSprite;
}

void Game::moveLeft()
{
	xAxisOfTheBlock -= 1;
}

void Game::moveRight()
{
	xAxisOfTheBlock += 1;
}

void Game::moveFaster()
{

}

void Game::moveRotate()
{

}

int** Game::generateTetrisFigure()
{
	srand((unsigned)time(NULL));
	int whichFigure = rand() % 7;
	int** figureMatrix = new int*[4];
	//int figureMatrix[2][4] = { {0} }; // = { {0} }; means "fill the matrix with zeroes"

	for (int h = 0; h < 4; h++)
	{
		figureMatrix[h] = new int[4];

		for (int w = 0; w < 4; w++)
		{
			figureMatrix[h][w] = 0;
		}
	}

	int figures[7][4] =
	{			//	x (%2)		y (/2)
		1,3,5,7, //(1,1,1,1) (0,1,2,3)
		2,4,5,7, //(0,0,1,1) (1,2,2,3)
		3,5,4,6, //(1,1,0,0) (1,2,2,3)
		3,5,4,7, //(1,1,0,1) (1,2,2,3)
		2,3,5,7, //(0,1,1,1) (0,1,2,3)
		3,5,7,6, //(1,1,1,0) (1,2,3,3)
		2,3,4,5, //(0,1,0,1) (1,1,2,2)
	};

	for (int i = 0; i < 4; i++)
		figureMatrix[figures[whichFigure][i] % 2] [figures[whichFigure][i] / 2] = 1; 

	return figureMatrix;
}

sf::Color Game::generateColorOfTetrisFigure()
{
	srand((unsigned)time(NULL));
	sf::Color randomColor(rand() % 255, rand() % 255, rand() % 255, 223);
	return randomColor;
}


sf::Texture Game::loadTetrisFigureTexture()
{
	sf::Texture tetris_figure_texture;
	if (!tetris_figure_texture.loadFromFile("resources/imgs/tetris-figure.jpg"))
		sf::err();
	tetris_figure_texture.setSmooth(true);

	return tetris_figure_texture;
}

sf::Sprite Game::createFigureSprite(sf::Texture & tetris_figure_texture)
{
	sf::Sprite menuSprite;
	menuSprite.setTexture(tetris_figure_texture);

	return menuSprite;
}