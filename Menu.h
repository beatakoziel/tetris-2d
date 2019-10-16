#pragma once

#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	bool visible = true;
	Menu(float width, float height);
	void drawTextInMenu(sf::RenderWindow &window);
	void moveUp();
	void moveDown();
	int getPressedItem() { return selectedItemIndex;  }
	sf::Texture loadMenuBackground();
	sf::Sprite createMenuSprite(sf::Texture &background_menu);

private:
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	int selectedItemIndex;
	sf::Font font;
	sf::Color activeOptionColor = sf::Color(222, 135, 47, 255);
	sf::Color inactiveOptionColor = sf::Color::White;

	void loadMenuFont();
	void initializeMenuOptions(float width, float height, sf::Color activeOptionColor, sf::Color inactiveOptionColor);
};

