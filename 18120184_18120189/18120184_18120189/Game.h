#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include "Ball.h"
#include "paddle.h"

const int HEIGHT = 480;
const int WIDTH = 640;
const int WALL_THICKNESS = 20;
const sf::Time TimePerFrame = sf::seconds(1.f / 144.f);

class Game
{
private:
	bool flag = true;
	sf::Text tPointP1;
	sf::Text tPointP2;
	sf::Text text;
	sf::Font font;
	int pointP1;
	int pointP2;
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
	int isOver();
	bool isCollisionWithP1();
	bool isCollisionWithP2();
	bool isCollisionWithWalls();
	void updatePlayerMovement(sf::Time dt);
	void updateBallMovement(sf::Time dt);
	void displayGameFinish();
	void resetStat(sf::Time dt);
	void run();
	void handleInput(sf::Keyboard::Key k, bool isPressed);
};

