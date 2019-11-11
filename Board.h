#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include "BoardSquare.h"
#include "Figure.h"

class Board
{
public:
	Board();
	Board(int xSize, sf::Texture squareTexture);
	void drawBoard(sf::RenderWindow &window);
	void changeColorsOfLines();
	void setPresenceInWholeBoard(Figure figure);
	//bool canFigureMove(Point* squaresPoints);
	void printMatrix();
	bool leftCollisions(Figure figure);
	bool rightCollisions(Figure figure);
	bool downCollisions(Figure figure);
	int checkLineOfSquares();
	void showScore(sf::RenderWindow & window, int scoreP);

private:
	int columns;
	sf::Color generateColor();
	void drawVerticalLine(sf::RenderWindow & window, int where, sf::Color color, sf::Color color2);
	void drawHorizontalLine(sf::RenderWindow & window, int where, sf::Color color, sf::Color color2, int xAxis);
	void drawSquareBox(sf::RenderWindow & window, int x, int y);
	sf::Color emptyBoxColor;
	sf::Color color;
	sf::Color color2;
	sf::Texture squareTexture;
	//std::vector<std::vector<BoardSquare>> boardSquare;
	BoardSquare **boardSquare;
	void convertCoordinatesToMatrixPosition(int & x, int & y);
	sf::Font font;
	void cleanUpMatrix(int whichRaw);
	void moveMatrixDown(int howMuch);
};

