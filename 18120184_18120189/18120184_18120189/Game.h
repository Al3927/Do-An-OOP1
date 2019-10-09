#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

const int HEIGHT = 480;
const int WIDTH = 640;
const int WALL_THICKNESS = 20;
const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

class Game
{
private:
	sf::RectangleShape leftWall;
	sf::RectangleShape rightWall;
	sf::RectangleShape upperWall;
	sf::RectangleShape lowerWall;
	sf::RenderWindow window;
	Ball ball;
private:
	void processEvents();
	void update(sf::Time dt);
	void render();
public:
	Game();
	void run();
};

