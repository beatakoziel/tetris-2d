#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	sf::Texture loadGameBackground();
	sf::Sprite createGameSprite(sf::Texture &background_menu, int xScreenDimension, int yScreenDimension);
};

