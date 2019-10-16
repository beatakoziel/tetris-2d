#pragma once

#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu(float width, float height);
	void loadMenuFont();
	void initializeMenuOptions(float width, float height);
	~Menu();

	void drawTextInMenu(sf::RenderWindow &window);
	void moveUp();
	void moveDown();
	int getPressedItem() { return selectedItemIndex;  }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

