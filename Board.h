#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include "BoardSquare.h"

class Board
{
public:
	Board();
	Board(int xSize, sf::Texture squareTexture);
	void drawBoard(sf::RenderWindow &window);
	void changeColorsOfLines();
	void setPresenceInWholeBoard(int x, int y);

private:
	int columns;
	sf::Color generateColor();
	void drawVerticalLine(sf::RenderWindow & window, int where, sf::Color color, sf::Color color2);
	void drawHorizontalLine(sf::RenderWindow & window, int where, sf::Color color, sf::Color color2, int xAxis);
	void drawSquareBox(sf::RenderWindow & window, int x, int y);
	sf::Color color;
	sf::Color color2;
	sf::Texture squareTexture;
	BoardSquare **boardSquare;
};

