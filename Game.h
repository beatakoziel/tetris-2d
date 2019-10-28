#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	sf::Texture loadGameBackground();
	sf::Sprite createGameSprite(sf::Texture &background_menu, int xScreenDimension, int yScreenDimension);
	void moveLeft();
	void moveRight();
	void moveFaster();

	void moveRotate();

	int** generateTetrisFigure();

	sf::Color generateColorOfTetrisFigure();
	sf::Texture loadTetrisFigureTexture();

	sf::Sprite createFigureSprite(sf::Texture & tetris_figure_texture);

private:
	int xAxisOfTheBlock;
};

