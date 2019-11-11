#pragma once
#include <SFML/Graphics.hpp>

class BoardSquare
{
public:
	bool isPresent();
	void setPresence(bool isPresent);

	sf::Color getColor();
	void setColor(sf::Color color);

	sf::Sprite getSquareSprite();

private:
	bool figureSquarePresence;
	sf::Color figureSquareColor;
	sf::Sprite squareSprite;
};

