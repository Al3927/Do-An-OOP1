#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <ctime>
#include "Ball.h"
#include "paddle.h"

const int HEIGHT = 480;
const int WIDTH = 640;
const int WALL_THICKNESS = 20;
const sf::Time TimePerFrame = sf::seconds(1.f / 144.f);
const sf::Time DelayTime = sf::seconds(1);
const int finishPoint = 10;

class Game
{
private:
  sf::Clock c;
	bool flag = false;
	sf::Text instruct;
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
	bool isPause;
private:
	void processEvents();
	void update(sf::Time dt);
	void render();
public:
	Game();
	~Game();
	int isOver();
	bool isCollisionWithP1();
	bool isCollisionWithP2();
	bool isCollisionWithWalls();
	void updatePlayerMovement(sf::Time dt);
	void updateBallMovement(sf::Time dt);
	void countPoint();
	bool checkFinish();
	void convertToText();
	void resetStat(sf::Time dt);
	void run();
	void handleInput(sf::Keyboard::Key k, bool isPressed);
};

