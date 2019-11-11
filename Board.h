#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>

class Board
{
public:
	Board();
	void drawBoard(int xAxis, sf::RenderWindow &window);
	void changeColors();
private:
	sf::Color generateColor();
	void drawVerticalLine(sf::RenderWindow & window, int where, sf::Color color, sf::Color color2);
	void drawHorizontalLine(sf::RenderWindow & window, int where, sf::Color color, sf::Color color2, int xAxis);
	sf::Color color;
	sf::Color color2;
};

