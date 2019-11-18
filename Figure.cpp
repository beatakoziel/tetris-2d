#include "pch.h"
#include "Figure.h"
#include <iostream>


Figure::Figure()
{
	this->figureTexture = loadFigureTexture();
	this->figureSprite = createFigureSprite(figureTexture);
	this->figureMatrix = generateFigureMatrix();
	this->color = generateColorOfTetrisFigure();
	figureSprite.setColor(color);
}

void Figure::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		float squareX = this->squaresCoordinates[i].getX();
		float squareY = this->squaresCoordinates[i].getY();
		sf::Sprite currentSquareSprite;
		currentSquareSprite.setPosition(squareX, squareY);
		window.draw(currentSquareSprite);
	}
}

void Figure::moveLeft(sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		float squareX = this->squaresCoordinates[i].getX();
		this->squaresCoordinates[i].setX(squareX - this->speed);
		this->figureSprite.setPosition(squaresCoordinates[i].getX(), squaresCoordinates[i].getY());
		window.draw(this->figureSprite);
	}
	findLastSquare();
}

void Figure::moveRight(sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		float squareX = this->squaresCoordinates[i].getX();
		this->squaresCoordinates[i].setX(squareX + this->speed);
		this->figureSprite.setPosition(squaresCoordinates[i].getX(), squaresCoordinates[i].getY());
		window.draw(this->figureSprite);
	}
	findLastSquare();
}

void Figure::moveDown(sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		float squareY = this->squaresCoordinates[i].getY();
		this->squaresCoordinates[i].setY(squareY + this->speed);
		this->figureSprite.setPosition(squaresCoordinates[i].getX(), squaresCoordinates[i].getY());
		window.draw(this->figureSprite);
	}
	findLastSquare();
}

void Figure::moveDownFaster(sf::RenderWindow &window)
{
	for (int i = 0; i < 4; i++)
	{
		float squareY = this->squaresCoordinates[i].getY();
		this->squaresCoordinates[i].setY(squareY + this->speed);
		this->figureSprite.setPosition(squaresCoordinates[i].getX(), squaresCoordinates[i].getY());
		window.draw(this->figureSprite);
	}
	findLastSquare();
}

void Figure::moveRotate(sf::RenderWindow &window)
{
	Point pivot = { squaresCoordinates[1].getX(), squaresCoordinates[1].getY() };

	for (int i = 0; i < 4; i++) {
		std::cout << (int)squaresCoordinates[i].getX() << ", " << (int)squaresCoordinates[i].getY() << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < 4; i++) {
		//if (i == 1) continue;
		/*int vX = (int)squaresCoordinates[i].getX();
		int vY = (int)squaresCoordinates[i].getY();

		int vrX = vX - (int)pivot.getX();
		int vrY = vY - (int)pivot.getY();

		int vtX = vX * vrX;
		int vtY = vY * vrY;

		int x = (int)pivot.getX() + vtX;
		int y = (int)pivot.getY() + vtY;*/
		int x = (int)squaresCoordinates[i].getX();
		int y = (int)squaresCoordinates[i].getY();

		int vrX = x - pivot.getX();
		int vrY = y - pivot.getY();
		int vtX = (-1)*vrY;
		int vtY = 1 * vrX;

		int resultX = pivot.getX() + vrX;
		int resultY = pivot.getY() + vrY;
		/*x -= (int)pivot.getX();
		y -= (int)pivot.getY();

		x *= (int)pivot.getY();
		y *= (int)pivot.getX();

		x += (int)pivot.getX();
		y += (int)pivot.getY();*/

		std::cout << resultX << ", " << resultY << std::endl;
		float squareX = this->squaresCoordinates[i].getX();
		float squareY = this->squaresCoordinates[i].getY();
		this->squaresCoordinates[i].setX(resultX);
		this->figureSprite.setPosition(squaresCoordinates[i].getX(), squaresCoordinates[i].getY());
		this->squaresCoordinates[i].setY(resultY);
		this->figureSprite.setPosition(squaresCoordinates[i].getX(), squaresCoordinates[i].getY());
		window.draw(this->figureSprite);
	}
	std::cout << std::endl;
}

int** Figure::generateFigureMatrix()
{
	srand((unsigned)time(NULL));
	int whichFigure = rand() % 7;
	int** figureMatrix = new int*[4];
	//int figureMatrix[2][4] = { {0} }; // = { {0} }; means "fill the matrix with zeroes"

	for (int h = 0; h < 4; h++)
	{
		figureMatrix[h] = new int[4];

		for (int w = 0; w < 4; w++)
			figureMatrix[h][w] = 0;
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
		figureMatrix[figures[whichFigure][i] % 2][figures[whichFigure][i] / 2] = 1;

	return figureMatrix;
}

sf::Color Figure::generateColorOfTetrisFigure()
{
	srand((unsigned)time(NULL));
	sf::Color randomColor(128 + rand() % 127, 128 + rand() % 127, 128 + rand() % 127, 223);
	return randomColor;
}

sf::Color Figure::getColor()
{
	return this->color;
}

sf::Texture Figure::getTexture()
{
	return this->figureTexture;
}


sf::Texture Figure::loadFigureTexture()
{
	sf::Texture tetris_figure_texture;
	if (!tetris_figure_texture.loadFromFile("resources/imgs/tetris-figure.jpg"))
		sf::err();
	tetris_figure_texture.setSmooth(true);

	return tetris_figure_texture;
}

sf::Sprite Figure::createFigureSprite(sf::Texture & tetris_figure_texture)
{
	sf::Sprite menuSprite;
	menuSprite.setTexture(tetris_figure_texture);

	return menuSprite;
}

int** Figure::getFigureMatrix()
{
	return this->figureMatrix;
}

sf::Sprite Figure::getFigureSprite()
{
	return this->figureSprite;
}

Point* Figure::getSquaresCoordinates()
{
	return this->squaresCoordinates;
}

Point Figure::getLastSquaresCoordinates()
{
	return this->lastSquareCoordinates;
}

void Figure::setSquaresCoordinates(int whichSquare, Point coordinates)
{
	this->squaresCoordinates[whichSquare] = coordinates;
	if (whichSquare == 3)
	{
		findLastSquare();
	}
}

void Figure::findLastSquare()
{
	float arrayOfY[4];
	for (int i = 0; i < 4; i++)
		arrayOfY[i] = squaresCoordinates[i].getY();
	float min = arrayOfY[0];
	int indexOfMin = 0;
	for (int i = 0; i < 4; i++)
		if (min < arrayOfY[i])
			indexOfMin = i;
	this->lastSquareCoordinates = squaresCoordinates[indexOfMin];
}

