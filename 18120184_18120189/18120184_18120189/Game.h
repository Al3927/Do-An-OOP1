#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Ball.h"
#include "paddle.h"

const int HEIGHT = 480;
const int WIDTH = 640;
const int WALL_THICKNESS = 20;
const sf::Time TimePerFrame = sf::seconds(1.f / 144.f);

class Game
{
private:
	sf::RectangleShape upperWall;
	sf::RectangleShape lowerWall;
	paddle p1;
	paddle p2;
	sf::RenderWindow window;
	Ball ball;
private:
	void processEvents();
	void update(sf::Time dt);
	void render();
public:
	Game();
	void run();
	void handleInput(sf::Keyboard::Key k, bool isPressed);
};

