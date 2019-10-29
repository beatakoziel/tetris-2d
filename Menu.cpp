#include "pch.h"
#include "Menu.h"
#include <iostream>


Menu::Menu(float width, float height)
{
	loadMenuFont();
	initializeMenuOptions(width, height, activeOptionColor, inactiveOptionColor);
}

void Menu::drawTextInMenu(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(inactiveOptionColor);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(activeOptionColor);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(inactiveOptionColor);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(activeOptionColor);
	}
}

sf::Texture Menu::loadMenuBackground()
{
	sf::Texture background_menu;
	if (!background_menu.loadFromFile("resources/imgs/back-yellow.png"))
		sf::err();
	background_menu.setSmooth(true);

	return background_menu;
}

sf::Sprite Menu::createMenuSprite(sf::Texture & background_menu)
{
	sf::Vector2i screenDimensions(1280, 720);
	sf::Sprite menuSprite;
	menuSprite.setTexture(background_menu);
	menuSprite.setScale((float)screenDimensions.x / background_menu.getSize().x, (float)screenDimensions.y / background_menu.getSize().y);

	return menuSprite;
}

void Menu::loadMenuFont()
{
	if (!font.loadFromFile("resources/fonts/CuteJellyfish.ttf"))
		if (!font.loadFromFile("resources/fonts/LemonBrush.otf"))
			if (!font.loadFromFile("resources/fonts/Sketch3D.otf"))
				sf::err();
}

void Menu::initializeMenuOptions(float width, float height, sf::Color activeOptionColor, sf::Color inactiveOptionColor)
{
	menu[0].setFont(font);
	menu[0].setScale(1.4f, 1.4f);
	menu[0].setFillColor(activeOptionColor);
	menu[0].setString("Play!");
	sf::FloatRect menuRect0 = menu[0].getLocalBounds();
	menu[0].setOrigin(menuRect0.left + menuRect0.width / 2.0f, menuRect0.top + menuRect0.height / 2.0f);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setScale(1.4f, 1.4f);
	menu[1].setFillColor(inactiveOptionColor);
	menu[1].setString("Options");
	sf::FloatRect menuRect1 = menu[1].getLocalBounds();
	menu[1].setOrigin(menuRect1.left + menuRect1.width / 2.0f, menuRect1.top + menuRect1.height / 2.0f);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setScale(1.4f, 1.4f);
	menu[2].setFillColor(inactiveOptionColor);
	menu[2].setString("Exit");
	sf::FloatRect menuRect2 = menu[2].getLocalBounds();
	menu[2].setOrigin(menuRect2.left + menuRect2.width / 2.0f, menuRect2.top + menuRect2.height / 2.0f);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}
