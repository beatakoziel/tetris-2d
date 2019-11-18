#pragma once

#include <SFML/Graphics.hpp>
#include "Point.h"
#include <iostream>
#include <cmath>

#define M_PI 3.14159265358979323846

class Figure
{
public:
	Figure();
	void draw();
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveDownFaster(sf::RenderWindow &window);
	void moveRotate();
	int** generateFigureMatrix();
	sf::Color generateColorOfTetrisFigure();
	sf::Texture loadFigureTexture();
	sf::Sprite createFigureSprite(sf::Texture &tetrisFigureTexture);
	int** getFigureMatrix();
	sf::Sprite getFigureSprite();
	Point* getSquaresCoordinates();
	Point getLastSquaresCoordinates();
	void setSquaresCoordinates(int whichSquare, Point coordinates);
	sf::Color getColor();
	sf::Texture getTexture();
	void findLastSquare();

private:
	int speed = 32;
	Point squaresCoordinates[4];
	Point lastSquareCoordinates;
	sf::Texture figureTexture;
	sf::Sprite figureSprite;
	int** figureMatrix;
	sf::Color color;
	int whichFigure;
};
