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

void Figure::draw()
{
	for (int i = 0; i < 4; i++)
	{
		float squareX = this->squaresCoordinates[i].getX();
		float squareY = this->squaresCoordinates[i].getY();
		sf::Sprite currentSquareSprite;
		currentSquareSprite.setPosition(squareX, squareY);
	}
}

void Figure::moveLeft()
{
	for (int i = 0; i < 4; i++)
	{
		float squareX = this->squaresCoordinates[i].getX();
		this->squaresCoordinates[i].setX(squareX - this->speed);
		this->figureSprite.setPosition(squaresCoordinates[i].getX(), squaresCoordinates[i].getY());
	}
	findLastSquare();
}

void Figure::moveRight()
{
	for (int i = 0; i < 4; i++)
	{
		float squareX = this->squaresCoordinates[i].getX();
		this->squaresCoordinates[i].setX(squareX + this->speed);
		this->figureSprite.setPosition(squaresCoordinates[i].getX(), squaresCoordinates[i].getY());
	}
	findLastSquare();
}

void Figure::moveDown()
{
	for (int i = 0; i < 4; i++)
	{
		float squareY = this->squaresCoordinates[i].getY();
		this->squaresCoordinates[i].setY(squareY + this->speed);
		this->figureSprite.setPosition(squaresCoordinates[i].getX(), squaresCoordinates[i].getY());
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

void Figure::moveRotate(int columns, BoardSquare** boardSquare)
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << "x=" << this->squaresCoordinates[i].getX() << "y=" << this->squaresCoordinates[i].getY() << std::endl;
	}
	std::cout << std::endl;

	Point origin;
	int x, y;
	int minX = squaresCoordinates[0].getX();
	int minY = squaresCoordinates[0].getY();
	int maxX = squaresCoordinates[0].getX();
	int maxY = squaresCoordinates[0].getY();
	int widthX = 32 * (columns-1);
	int additionalValue = 0;
	bool canMove = true;
	for (int i = 0; i < 4; i++)
	{
		if (squaresCoordinates[i].getX() < minX)
			minX = squaresCoordinates[i].getX();
		if (squaresCoordinates[i].getX() > maxX)
			maxX = squaresCoordinates[i].getX();
		if (squaresCoordinates[i].getY() < minY)
			minY = squaresCoordinates[i].getY();
		if (squaresCoordinates[i].getY() > maxY)
			maxY = squaresCoordinates[i].getY();
	}

	if (minX >= widthX)
	{
		std::cout << "przy krawedzi" << std::endl;
		additionalValue = 0;
		 origin = Point(maxX, maxY);
	}
	else {
		std::cout << "nie przy krawedzi" << std::endl;
		additionalValue = 64;
		origin = Point(minX, minY);
	}
	Point rotatedCoordinates[4];



		for (int i = 0; i < 4; i++) {

			Point translationCoordinate =  Point(squaresCoordinates[i].getX() - origin.getX(), squaresCoordinates[i].getY() - origin.getY());
			translationCoordinate.setY(translationCoordinate.getY()*-1);
			translationCoordinate.setY(translationCoordinate.getY()*1);

			rotatedCoordinates[i].setX(translationCoordinate.getX());
			rotatedCoordinates[i].setY(translationCoordinate.getY());

			rotatedCoordinates[i].setX( (int)round(translationCoordinate.getX() * cos(M_PI / 2) - translationCoordinate.getY() * sin(M_PI / 2)));
			rotatedCoordinates[i].setY( (int)round(translationCoordinate.getX() * sin(M_PI / 2) + translationCoordinate.getY() * cos(M_PI / 2)));

			rotatedCoordinates[i].setY(rotatedCoordinates[i].getY()*-1);
			rotatedCoordinates[i].setY(rotatedCoordinates[i].getY()*1);

			rotatedCoordinates[i].setX(rotatedCoordinates[i].getX() + origin.getX());
			rotatedCoordinates[i].setY(rotatedCoordinates[i].getY() + origin.getY());

			x = (int)rotatedCoordinates[i].getX();
			y = (int)rotatedCoordinates[i].getY();
			x -= 32;
			x /= 32;
			y /= 32;
			if (y >= 19)
				canMove = false;
			if (x >= 0 && y >= 0 && y < 19)
				if (boardSquare[y + 1][x].isPresent())
					canMove = false;
		}

		if(canMove)
			for (int i = 0; i < 4; i++)
			{
				squaresCoordinates[i].setX(rotatedCoordinates[i].getX());
				squaresCoordinates[i].setY(rotatedCoordinates[i].getY() + additionalValue);
			}

		findLastSquare();
}

int** Figure::generateFigureMatrix()
{
	srand((unsigned)time(NULL));
	int whichFigure =  rand() % 7;
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
