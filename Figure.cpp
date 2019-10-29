#include "pch.h"
#include "Figure.h"


Figure::Figure()
{
	this->figureTexture = loadFigureTexture();
	this->figureSprite = createFigureSprite(figureTexture);
	this->figureMatrix = generateFigureMatrix();
	this->color = generateColorOfTetrisFigure();
	figureSprite.setColor(color);
}

void Figure::moveLeft()
{
}

void Figure::moveRight()
{

}

void Figure::moveDown()
{
	for (int i = 0; i < 4; i++)
	{
		float squareX = this->squaresCoordinates[i].getX();
		this->squaresCoordinates[i].setX(squareX + this->speed);
		float squareY = this->squaresCoordinates[i].getY();
		this->squaresCoordinates[i].setY(squareY + this->speed);
		this->figureSprite.setPosition(squaresCoordinates[i].getX(), squaresCoordinates[i].getY());
	}
		
}

void Figure::moveDownFaster()
{

}

void Figure::moveRotate()
{

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
	sf::Color randomColor(rand() % 255, rand() % 255, rand() % 255, 223);
	return randomColor;
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

Point* Figure::getSquaresPosition()
{
	return this->squaresCoordinates;
}

void Figure::setSquaresPosition(int whichSquare, Point coordinates)
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
		if (min > arrayOfY[i])
			indexOfMin = i;
	this->lastSquareCoordinates = squaresCoordinates[indexOfMin];
}