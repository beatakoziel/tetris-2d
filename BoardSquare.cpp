#include "pch.h"
#include "BoardSquare.h"

bool BoardSquare::isPresent()
{
	return this -> figureSquarePresence;
}

void BoardSquare::setPresence(bool isPresent)
{
     this -> figureSquarePresence = isPresent;
}

sf::Color BoardSquare::getColor()
{
	return this->figureSquareColor;
}

void BoardSquare::setColor(sf::Color color)
{
    this->figureSquareColor = color;
}
/* usun :c
sf::Sprite BoardSquare::getSquareSprite()
{
	return this->squareSprite;
}

void BoardSquare::setSquareSprite(sf::Color color)
{
	this->figureSquareColor = color;
}*/ 