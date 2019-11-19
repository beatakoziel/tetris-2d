#pragma once

void generateFigure( sf::RenderWindow &window, int maximumX);

void setUpNextAndCurrentFigure(sf::RenderWindow &window);

void drawCurrentFigure(sf::Texture &squareTexture, sf::RenderWindow &window);

void drawNextFigure(float &differenceX, float &differenceY, sf::Texture &squareTexture, sf::RenderWindow &window);
