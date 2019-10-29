#include "pch.h"
#include "Game.h"
#include <time.h>
#include <iostream>

sf::Texture Game::loadGameBackground()
{
	sf::Texture background_game;
	if (!background_game.loadFromFile("resources/imgs/game-background.jpg"))
		sf::err();

	return background_game;
}

sf::Sprite Game::createGameSprite(sf::Texture & background_game, int xScreenDimension, int yScreenDimension)
{
	sf::Vector2i screenDimensions(xScreenDimension, yScreenDimension);
	sf::Sprite gameSprite;
	gameSprite.setTexture(background_game);
	gameSprite.setScale(1.0f, (float)screenDimensions.y / background_game.getSize().y);

	return gameSprite;
}

