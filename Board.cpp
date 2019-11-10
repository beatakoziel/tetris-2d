#include "pch.h"
#include "Board.h"

Board::Board()
{
	this->color = generateColor();
	this->color2 = generateColor();
}

void Board::drawBoard(int xAxis, sf::RenderWindow &window)
{
	for(int i=0; i < xAxis; i++)
		drawVerticalLine(window, i, color, color2);

	for(int i=0; i <= 20; i++)
		drawHorizontalLine(window, i, color, color2, xAxis);
} 

sf::Color Board::generateColor()
{
	sf::Color color(-rand() % 255, -rand() % 255, -rand() % 255); 
	if (color != sf::Color::Black)
		return color;
	return sf::Color::Magenta;
}

void Board::drawVerticalLine(sf::RenderWindow &window, int where, sf::Color color, sf::Color color2)
{
	sf::Vertex line[2] =
	{
		sf::Vertex(sf::Vector2f(32 * (float)where, 0.f), color),
		sf::Vertex(sf::Vector2f(32 * (float)where, 640.f), color2)
	};
	window.draw(line, 2, sf::Lines);
}

void Board::drawHorizontalLine(sf::RenderWindow &window, int where, sf::Color color, sf::Color color2, int xAxis)
{
	where *= 32;
	--xAxis;

	sf::Vertex line[2] =
	{
		sf::Vertex(sf::Vector2f((float)32, (float)where), color),
		sf::Vertex(sf::Vector2f((float)32 * xAxis, (float)where), color2)
	};
	window.draw(line, 2, sf::Lines);
}
