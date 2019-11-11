#include "pch.h"
#include "Board.h"

Board::Board()
{
	this->color = generateColor();
	this->color2 = generateColor();
}

Board::Board(int xSize, sf::Texture squareTexture) //ySize = 20
{
	this->color = generateColor();
	this->color2 = generateColor();
	this->columns = xSize;
	this->squareTexture = squareTexture;

	this->boardSquare = new BoardSquare*[xSize];
	for (int i = 0; i < xSize; ++i)
		this->boardSquare[i] = new BoardSquare[20];

	for (int i = 0; i < xSize; i++)
		for (int j = 0; j < 20; j++)
		{
			this->boardSquare[i][j].setPresence(false);
			this->boardSquare[i][j].setColor(sf::Color::Color(128, 128, 128, 64));
		}
}

void Board::drawBoard(sf::RenderWindow &window)
{
	for (int i = 0; i < columns + 2; i++) 
		drawVerticalLine(window, i, color, color2);

	for (int i = 0; i <= 20; i++)
		drawHorizontalLine(window, i, color, color2, columns);

	for (int i = 0; i < columns; i++)
		for (int j = 0; j < 20; j++)
			drawEmptySquareBox(window, i, j);
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
	++xAxis;

	sf::Vertex line[2] =
	{
		sf::Vertex(sf::Vector2f((float)32, (float)where), color),
		sf::Vertex(sf::Vector2f((float)32 * xAxis, (float)where), color2)
	};
	window.draw(line, 2, sf::Lines);
}

void Board::drawEmptySquareBox(sf::RenderWindow &window, int x, int y)
{
	sf::RectangleShape squareBox(sf::Vector2f(30, 30));
	squareBox.setPosition(32 + (x * 32), y * 32);
	squareBox.setFillColor(this->boardSquare[x][y].getColor());
	window.draw(squareBox);
}
