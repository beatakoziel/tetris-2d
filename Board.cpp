#include "pch.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>

Board::Board()
{
	changeColorsOfLines();
}

Board::Board(int xSize, sf::Texture squareTexture) //ySize = 20
{	
	this->emptyBoxColor = sf::Color::Color(128, 128, 128, 64);
	changeColorsOfLines();
	this->columns = xSize;
	this->squareTexture = squareTexture;

	this->boardSquare = new BoardSquare*[20];
	for (int i = 0; i < 20; ++i)
		this->boardSquare[i] = new BoardSquare[xSize];

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < xSize; j++)
		{
			this->boardSquare[i][j].setPresence(false);
			this->boardSquare[i][j].setColor(emptyBoxColor);
		}
}

void Board::drawBoard(sf::RenderWindow &window)
{
	for (int i = 0; i < columns + 2; i++) 
		drawVerticalLine(window, i, color, color2);

	for (int i = 0; i <= 20; i++)
		drawHorizontalLine(window, i, color, color2, columns);

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < columns; j++)
			drawSquareBox(window, i, j);
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

void Board::drawSquareBox(sf::RenderWindow &window, int x, int y)
{
	sf::RectangleShape squareBox(sf::Vector2f(30, 30));
	squareBox.setPosition((float)32 + (y * 32), (float)x* 32);

	if (this->boardSquare[x][y].isPresent())
		squareBox.setTexture(&(this -> squareTexture));

	squareBox.setFillColor(this->boardSquare[x][y].getColor());
	window.draw(squareBox);
}

void Board::changeColorsOfLines()
{
	this->color = generateColor();
	this->color2 = generateColor();
}

void Board::setPresenceInWholeBoard(Figure figure)
{
	for (int i = 0; i < 4; i++) {
		int x = (int)figure.getSquaresCoordinates()[i].getX();
		int y = (int)figure.getSquaresCoordinates()[i].getY();
		sf::Color color = figure.getColor();
		convertCoordinatesToMatrixPosition(x, y);
		if (x >= 0 && y >= 0 && y < 20) {
			//++y;
			this->boardSquare[y][x].setPresence(true);
			if(this->boardSquare[y][x].getColor() == emptyBoxColor)
				this->boardSquare[y][x].setColor(color);
		}
	}
}

void Board::convertCoordinatesToMatrixPosition(int& x, int& y)
{
	x -= 32;
	x /= 32;
	y /= 32;
}

void Board::printMatrix()
{
	int a;
	for (int i = 0; i < 20; i++) {
		std::cout << i << ".\t";
		for (int j = 0; j < this->columns; j++)
		{
			if (boardSquare[i][j].isPresent())
				a = 1;
			else a = 0;
			std::cout << a << ",";
		}
		std::cout <<"\n";
	}
	std::cout << "\n\n";
}

bool Board::leftCollisions(Figure figure)
{
	int x, y;
	for (int i = 0; i < 4; i++)
	{
		x = (int)figure.getSquaresCoordinates()[i].getX();
		y = (int)figure.getSquaresCoordinates()[i].getY();
		convertCoordinatesToMatrixPosition(x, y);
		if(x < 1)
			return false;
		if (x >= 0 && y >= 0)
			if (boardSquare[y][x - 1].isPresent())
				return false;
	}
	return true;
}

bool Board::rightCollisions(Figure figure)
{
	int x, y;
	for (int i = 0; i < 4; i++)
	{
		x = (int)figure.getSquaresCoordinates()[i].getX();
		y = (int)figure.getSquaresCoordinates()[i].getY();
		convertCoordinatesToMatrixPosition(x, y);
		if (x > this->columns - 2)
			return false;
		if (x >= 0 && y >= 0)
			if (boardSquare[y][x+1].isPresent())
				return false;
	}
	return true;
}

bool Board::downCollisions(Figure figure)
{
	int x, y;
	for (int i = 0; i < 4; i++)
	{
		x = (int)figure.getSquaresCoordinates()[i].getX();
		y = (int)figure.getSquaresCoordinates()[i].getY();
		convertCoordinatesToMatrixPosition(x, y);
		if (y >= 19)
			return false;
		if (x >= 0 && y >= 0 && y < 19)
			if (boardSquare[y + 1][x].isPresent())
				return false;
	}
	return true;
}

void Board::cleanUpMatrix(int whichRaw)
{
	for (int i = 0; i < columns; i++) {
		boardSquare[whichRaw][i].setPresence(false);
		boardSquare[whichRaw][i].setColor(emptyBoxColor);
	}

}

void Board::moveMatrixDown(int howMuch, int fromWhere)
{
	int shift = howMuch;
	for (int i = fromWhere; i >= 0; i--)
		for (int j = 0; j < columns; j++)
		{
			shift = howMuch;
			while ((i + shift) > 19)
			{
				--shift;
			}

			boardSquare[i + shift][j].setColor(boardSquare[i][j].getColor());
			boardSquare[i + shift][j].setPresence(boardSquare[i][j].isPresent());
		}
}

int Board::checkLineOfSquares()
{
	int sumOfSquares[20] = { 0 }, strike = 0, fromWhere = 0;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < columns; j++)
			if (boardSquare[i][j].isPresent())
				++sumOfSquares[i];

		if (sumOfSquares[i] == columns)
		{
			fromWhere = i-1;
			strike++;
			cleanUpMatrix(i);
		}
	}

	if (strike > 0) 
	{
		moveMatrixDown(strike, fromWhere);
		changeColorsOfLines();	
		sf::Music strikeMusic;
		if (!strikeMusic.openFromFile("resources/sounds/strike.ogg"))
			std::cout << "cant open game music";
		strikeMusic.play();
	}
	strike *= strike;
	return strike;
}

void Board::showScore(sf::RenderWindow &window, int scoreP)
{
	if (!font.loadFromFile("resources/fonts/Sketch3D.otf"))
		sf::err();

	sf::Text text;	
	text.setFont(font);
	text.setFillColor(color);
	text.setCharacterSize(24);
	text.setString("SCORE: " + std::to_string(scoreP));
	text.setPosition((float)(columns * 32) + 64, 100.f);

	window.draw(text);
}

BoardSquare ** Board::getBoardSquare()
{
	return this->boardSquare;
}

bool Board::isItEndOfTheTetris()
{
	for (int i = 0; i < columns; i++)
		if (boardSquare[0][i].isPresent())
			return true;
	return false;
}

