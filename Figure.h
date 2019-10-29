#pragma once

#include <SFML/Graphics.hpp>
#include "Point.h"

class Figure
{
public:
	Figure();
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveDownFaster();
	void moveRotate();
	int** generateFigureMatrix();
	sf::Color generateColorOfTetrisFigure();
	sf::Texture loadFigureTexture();
	sf::Sprite createFigureSprite(sf::Texture &tetrisFigureTexture);
	int** getFigureMatrix();
	sf::Sprite getFigureSprite();
	Point* getSquaresPosition();
	void setSquaresPosition(int whichSquare, Point coordinates);

	void findLastSquare();

private:
	int speed = 5;
	Point squaresCoordinates[4];
	Point lastSquareCoordinates;
	sf::Texture figureTexture;
	sf::Sprite figureSprite;
	int** figureMatrix;
	sf::Color color;
};
