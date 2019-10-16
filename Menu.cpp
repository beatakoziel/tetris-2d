#include "pch.h"
#include "Menu.h"


Menu::Menu(float width, float height)
{
	loadMenuFont();
	initializeMenuOptions(width, height);
}

void Menu::loadMenuFont()
{
	if (!font.loadFromFile("resources/fonts/CuteJellyfish.ttf"))
	{
		if (!font.loadFromFile("resources/fonts/LemonBrush.otf"))
		{
			if (!font.loadFromFile("resources/fonts/Sketch3D.otf"))
				sf::err();
		}
	}
}

void Menu::initializeMenuOptions(float width, float height)
{
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Green);
	menu[0].setString("Play!");
	sf::FloatRect menuRect0 = menu[0].getLocalBounds();
	menu[0].setOrigin(menuRect0.left + menuRect0.width / 2.0f, menuRect0.top + menuRect0.height / 2.0f);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	sf::FloatRect menuRect1 = menu[1].getLocalBounds();
	menu[1].setOrigin(menuRect1.left + menuRect1.width / 2.0f, menuRect1.top + menuRect1.height / 2.0f);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	sf::FloatRect menuRect2 = menu[2].getLocalBounds();
	menu[2].setOrigin(menuRect2.left + menuRect2.width / 2.0f, menuRect2.top + menuRect2.height / 2.0f);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::drawTextInMenu(sf::RenderWindow &window)
{
	for(int i=0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}