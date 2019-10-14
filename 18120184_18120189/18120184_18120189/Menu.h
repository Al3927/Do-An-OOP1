#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"

class Menu
{
public:
	Menu(const int WIDTH, const int HEIGHT);
	~Menu();
	void draw(sf::RenderWindow& window);
};

