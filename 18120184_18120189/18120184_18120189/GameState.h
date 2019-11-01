#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
//#include "Game.h"

#include <cmath>
#include <string>
#include <ctime>
#include "Ball.h"
#include "paddle.h"


//Tran Dang Khoa 

const int HEIGHT = 480;
const int WIDTH = 720;
const int WALL_THICKNESS = 20;
const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
const sf::Time DelayTime = sf::seconds(1);
const int finishPoint = 10;


//
class GameState :
	public State
{
protected:
	//Tran Dang Khoa
	sf::Clock c;
	bool flag = false;
	sf::Text instruct;
	sf::Text tPointP1;
	sf::Text tPointP2;
	sf::Text text;
	
	int pointP1;
	int pointP2;
	sf::RectangleShape upperWall;
	sf::RectangleShape lowerWall;
	paddle p1;
	paddle p2;
	//sf::RenderWindow window;
	Ball ball;
	bool isPause;
	//
	sf::View view;
	sf::Vector2i viewGridPosition;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;


	//Player* player;

	sf::Texture texture;
	


	//Functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initvari();

	void initPauseMenu();

	//void initPlayers();


public:
	//Tran Dang Khoa

	int isOver();
	int isCollisionWithP1();
	int isCollisionWithP2();
	bool isCollisionWithWalls();
	virtual void updatePlayerMovement(const float& dt);
	void updateBallMovement(const float& dt);
	void countPoint();
	bool checkFinish();
	void convertToText();
	void resetStat(const float& dt);

	virtual void handleInput(sf::Keyboard::Key k, bool isPressed);

	//
	void updatePlayerInput();
	//
	GameState();
	GameState(StateData* state_data);
	virtual ~GameState();

	//Functions
	void loadGame(const std::string path);
	void saveGame(const std::string path);
	void updateInput(const float& dt);

	virtual void updatePauseMenuButtons();


	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif