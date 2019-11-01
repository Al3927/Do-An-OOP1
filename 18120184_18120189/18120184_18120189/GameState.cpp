#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 
			0, 
			this->stateData->gfxSettings->resolution.width, 
			this->stateData->gfxSettings->resolution.height
		)
	);
}

//Initializer functions
void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initvari()
{
	isPause = 0;
	srand(time(NULL));
	//font.loadFromFile("VCR_OSD_MONO_1.001.ttf");
	tPointP1.setFont(font);
	tPointP2.setFont(font);
	text.setFont(font);
	tPointP1.setString("0");
	tPointP2.setString("0");
	text.setString("");
	instruct.setString("Score 10 points first to win");
	instruct.setFillColor(sf::Color::White);
	instruct.setFont(font);
	instruct.setCharacterSize(25);
	instruct.setPosition(150, 50);
	text.setCharacterSize(30);
	tPointP1.setCharacterSize(35);
	tPointP2.setCharacterSize(35);
	text.setFillColor(sf::Color::Red);
	tPointP1.setFillColor(sf::Color::Red);
	tPointP2.setFillColor(sf::Color::Red);
	text.setPosition(150, 200);
	tPointP1.setPosition(50, 50);
	tPointP2.setPosition(650, 50);

	pointP1 = 0;
	pointP2 = 0;
	
	p1.setPosition(10, (this->stateData->gfxSettings->resolution.height - p1.getSize().y) / 2);
	p1.setFillColor(sf::Color::Green);
	p2.setPosition(this->stateData->gfxSettings->resolution.width - (10 + p2.getSize().x), (this->stateData->gfxSettings->resolution.height - p2.getSize().y) / 2);
	p2.setFillColor(sf::Color::Blue);
	ball.setPosition(this->stateData->gfxSettings->resolution.width / 2, this->stateData->gfxSettings->resolution.height / 2);
	upperWall.setSize(sf::Vector2f(this->stateData->gfxSettings->resolution.width, WALL_THICKNESS));
	upperWall.setPosition(0, 0);
	upperWall.setFillColor(sf::Color::Cyan);
	lowerWall.setSize(sf::Vector2f(this->stateData->gfxSettings->resolution.width, WALL_THICKNESS));
	lowerWall.setPosition(0, this->stateData->gfxSettings->resolution.height - WALL_THICKNESS);
	lowerWall.setFillColor(sf::Color::Cyan);


}



void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
	this->pmenu->addButton("SAVE_CASE_1", gui::p2pY(30.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Save Case 1");
	this->pmenu->addButton("SAVE_CASE_2", gui::p2pY(35.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Save Case 2");
	this->pmenu->addButton("SAVE_CASE_3", gui::p2pY(40.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Save Case 3");
	this->pmenu->addButton("LOAD_CASE_1", gui::p2pY(50.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Load Case 1");
	this->pmenu->addButton("LOAD_CASE_2", gui::p2pY(55.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Load Case 2");
	this->pmenu->addButton("LOAD_CASE_3", gui::p2pY(60.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Load Case 3");
}





void GameState::updatePlayerInput()
{

	sf::Event e;
	while (window->pollEvent(e)) 
	{
		switch (e.type) 
		{
			case sf::Event::Closed:
				window->close();
				break;

			case sf::Event::KeyPressed:
				handleInput(e.key.code, true);
				break;

			case sf::Event::KeyReleased:
			{
				handleInput(e.key.code, false);
				break;
			}

		}

	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("P1_MOVEUP"))))
	{
		if (!p1.getIsUp())
			p1.setIsUp(true);
		else
			p1.setIsUp(false);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("P1_MOVEDOWN"))))
	{
		if (!p1.getIsDown())
			p1.setIsDown(true);
		else
			p1.setIsDown(false);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("P2_MOVEUP"))))
	{
		if (!p2.getIsUp())
			p2.setIsUp(true);
		else
			p2.setIsUp(false);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("P2_MOVEDOWN"))))
	{
		if (!p2.getIsDown())
			p2.setIsDown(true);
		else
			p2.setIsDown(false);
	}*/
}

GameState::GameState()
{
}

//Constructors / Destructors
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initvari();
	this->initPauseMenu();

	//Tran Dang Khoa


}

GameState::~GameState()
{
	delete this->pmenu;

}

//Functions


void GameState::loadGame(const std::string path)
{
	std::ifstream ifs;
	//std::ifstream ifs("a.txt");
	ifs.open(path);

	if (ifs.is_open())
	{
		sf::Vector2f b_pos;
		ifs >> b_pos.x >> b_pos.y;
		ball.setPosition(b_pos);

		sf::Vector2f p1_pos = p1.getPosition();
		ifs >> p1_pos.x >> p1_pos.y;
		p1.setPosition(p1_pos);
		sf::Vector2f p2_pos = p2.getPosition();
		ifs >> p2_pos.x >> p2_pos.y;
		p2.setPosition(p2_pos);
		ifs >> pointP1;
		ifs >> pointP2;
	}

	ifs.close();
}

void GameState::saveGame(const std::string path)
{
	std::ofstream ifs;
	//std::ifstream ifs("a.txt");
	ifs.open(path);

	if (ifs.is_open())
	{
		sf::Vector2f b_pos = ball.getPosition();
		ifs << b_pos.x << " " << b_pos.y << "\n";
		sf::Vector2f p1_pos = p1.getPosition();
		ifs << p1_pos.x << " " << p1_pos.y << "\n";
		sf::Vector2f p2_pos = p2.getPosition();
		ifs << p2_pos.x << " " << p2_pos.y << "\n";
		ifs << pointP1 << "\n";
		ifs << pointP2 << "\n";
	}

	ifs.close();
}

void GameState::updateInput(const float & dt)
{
	
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
	
		
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}



void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
	if (this->pmenu->isButtonPressed("SAVE_CASE_1"))
		this->saveGame("case_1.txt");
	if (this->pmenu->isButtonPressed("SAVE_CASE_2"))
		this->saveGame("case_2.txt");
	if (this->pmenu->isButtonPressed("SAVE_CASE_3"))
		this->saveGame("case_3.txt");
	if (this->pmenu->isButtonPressed("LOAD_CASE_1"))
		this->loadGame("case_1.txt");
	if (this->pmenu->isButtonPressed("LOAD_CASE_2"))
		this->loadGame("case_2.txt");
	if (this->pmenu->isButtonPressed("LOAD_CASE_3"))
		this->loadGame("case_3.txt");
}





void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);	


	if (!this->paused) //Unpaused update
	{
		/*if (!checkFinish())
		{*/
			this->updatePlayerInput();

			if (isOver()) {
				countPoint();
				if (!checkFinish())
					resetStat(dt);
			}
			else {

				this->updatePlayerMovement(dt);
				updateBallMovement(dt);
			}
		


	}
	else //Paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();
	this->renderTexture.draw(text);
	//window->clear();
	//window->draw(text);
	this->renderTexture.draw(instruct);
	this->renderTexture.draw(upperWall);
	this->renderTexture.draw(lowerWall);
	this->renderTexture.draw(ball);
	this->renderTexture.draw(p1);
	this->renderTexture.draw(p2);
	this->renderTexture.draw(tPointP1);
	this->renderTexture.draw(tPointP2);
	this->renderTexture.display();

	this->renderTexture.setView(this->view);


	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());

	


	if (this->paused) //Pause menu render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//FINAL RENDER
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}

//Tran Dang Khoa

int GameState::isOver()
{
	if (ball.getPosition().x + ball.getRadius() <= 0)
		return 1;
	if (ball.getPosition().x - ball.getRadius() > this->stateData->gfxSettings->resolution.width)
		return -1;
	else return 0;
}

int GameState::isCollisionWithP1()
{
	if (ball.getPosition().x - ball.getRadius() <= p1.getPosition().x + p1.getSize().x &&
		ball.getPosition().x - ball.getRadius() >= p1.getPosition().x &&
		ball.getPosition().y >= p1.getPosition().y &&
		ball.getPosition().y <= p1.getPosition().y + p1.getSize().y)
		return 1;
	else
		if (ball.getPosition().x >= p1.getPosition().x + p1.getSize().x &&
			ball.getPosition().y <= p1.getPosition().y &&
			sqrt((p1.getPosition().x + p1.getSize().x - ball.getPosition().x) * (p1.getPosition().x + p1.getSize().x - ball.getPosition().x) +
			(ball.getPosition().y - p1.getPosition().y) * (ball.getPosition().y - p1.getPosition().y)) <= ball.getRadius())
			return 2;

		else if (ball.getPosition().x >= p1.getPosition().x + p1.getSize().x &&
			ball.getPosition().y >= p1.getPosition().y + p1.getSize().y &&
			sqrt((p1.getPosition().x + p1.getSize().x - ball.getPosition().x) * (p1.getPosition().x + p1.getSize().x - ball.getPosition().x) +
			(ball.getPosition().y - (p1.getPosition().y + p1.getSize().y)) * (ball.getPosition().y - (p1.getPosition().y + p1.getSize().y))) <= ball.getRadius())
			return 2;

		else if (ball.getPosition().x <= p1.getPosition().x + p1.getSize().x &&
			ball.getPosition().x >= p1.getPosition().x &&
			((ball.getPosition().y + ball.getRadius() >= p1.getPosition().y &&
				ball.getPosition().y + ball.getRadius() <= p1.getPosition().y + p1.getSize().x) ||
				(ball.getPosition().y - ball.getRadius() <= p1.getPosition().y + p1.getSize().y &&
					ball.getPosition().y - ball.getRadius() >= p1.getPosition().y + p1.getSize().y - p1.getSize().x)))
			return 3;
		else
			return 0;
}

int GameState::isCollisionWithP2()
{
	if (ball.getPosition().x + ball.getRadius() <= p2.getPosition().x + p2.getSize().x &&
		ball.getPosition().x + ball.getRadius() >= p2.getPosition().x &&
		ball.getPosition().y >= p2.getPosition().y &&
		ball.getPosition().y <= p2.getPosition().y + p2.getSize().y)
		return 1;
	else
		if (ball.getPosition().x <= p2.getPosition().x &&
			ball.getPosition().y <= p2.getPosition().y &&
			sqrt((p2.getPosition().x - ball.getPosition().x) * (p2.getPosition().x - ball.getPosition().x) +
			(ball.getPosition().y - p2.getPosition().y) * (ball.getPosition().y - p2.getPosition().y)) <= ball.getRadius())
			return 2;

		else if (ball.getPosition().x <= p2.getPosition().x &&
			ball.getPosition().y >= p2.getPosition().y + p2.getSize().y &&
			sqrt((p2.getPosition().x - ball.getPosition().x) * (p2.getPosition().x - ball.getPosition().x) +
			(ball.getPosition().y - (p2.getPosition().y + p2.getSize().y)) * (ball.getPosition().y - (p2.getPosition().y + p2.getSize().y))) <= ball.getRadius())
			return 2;

		else if (ball.getPosition().x <= p2.getPosition().x + p2.getSize().x &&
			ball.getPosition().x >= p2.getPosition().x &&
			((ball.getPosition().y + ball.getRadius() >= p2.getPosition().y &&
				ball.getPosition().y + ball.getRadius() <= p2.getPosition().y + p2.getSize().x) ||
				(ball.getPosition().y - ball.getRadius() <= p2.getPosition().y + p2.getSize().y &&
					ball.getPosition().y - ball.getRadius() >= p2.getPosition().y + p2.getSize().y - p2.getSize().x)))
			return 3;
		else
			return 0;
}

bool GameState::isCollisionWithWalls()
{
	return (ball.getPosition().y - ball.getRadius() <= WALL_THICKNESS || ball.getPosition().y + ball.getRadius() >= this->stateData->gfxSettings->resolution.height - WALL_THICKNESS);
}

void GameState::updatePlayerMovement(const float& dt)
{
	sf::Vector2f p1Movement(0, 0);
	sf::Vector2f p2Movement(0, 0);
	if (p1.getIsUp() && p1.getPosition().y >= WALL_THICKNESS)
		p1Movement.y -= p1.getSpeed();
	if (p1.getIsDown() && p1.getPosition().y <= this->stateData->gfxSettings->resolution.height - p1.getSize().y - WALL_THICKNESS)
		p1Movement.y += p1.getSpeed();
	if (p2.getIsUp() && p2.getPosition().y >= WALL_THICKNESS)
		p2Movement.y -= p2.getSpeed();
	if (p2.getIsDown() && p2.getPosition().y <= this->stateData->gfxSettings->resolution.height - p1.getSize().y - WALL_THICKNESS)
		p2Movement.y += p2.getSpeed();
	p1.move(p1Movement * dt);
	p2.move(p2Movement * dt);
}

void GameState::updateBallMovement(const float& dt)
{
	sf::Vector2f ballMovement(0, 0);
	float phi = ball.getAngle();
	float newAngle = phi;
	if (isCollisionWithWalls())
		newAngle = -phi;
	if (isCollisionWithP1()) {
		if (phi > 0)
			newAngle = (float)(rand() % 1100) / 1000;
		else
			newAngle = -(float)(rand() % 1100) / 1000;
		ball.setSpeed(ball.getSpeed() * 1.1);
	}

	if (isCollisionWithP2()) {
		if (phi > 0)
			newAngle = (PI - (float)(rand() % 1100) / 1000);
		else
			newAngle = -(PI - (float)(rand() % 1100) / 1000);
		ball.setSpeed(ball.getSpeed() * 1.1);
	}
	ball.setAngle(newAngle);
	sf::Vector2f direction(cos(ball.getAngle()), sin(ball.getAngle()));
	ballMovement += direction * ball.getSpeed();
	ball.move(ballMovement * dt);
}

void GameState::countPoint()
{
	if (!flag) {
		if (isOver() == -1)
			pointP1++;
		if (isOver() == 1)
			pointP2++;
		c.restart();
		flag = true;
		convertToText();
	}
}

bool GameState::checkFinish()
{
	if (pointP1 == finishPoint || pointP2 == finishPoint) {
		if (pointP1 == finishPoint)
			text.setString("P1 wins, Enter to play again");
		else
			text.setString("P2 wins, Enter to play again");
		return true;
	}
	return false;
}

void GameState::convertToText()
{
	std::string s1;
	std::string s2;
	s1 = std::to_string(pointP1);
	s2 = std::to_string(pointP2);
	tPointP1.setString(s1);
	tPointP2.setString(s2);
}

void GameState::resetStat(const float& dt)
{
	if (c.getElapsedTime() >= DelayTime) {
		flag = false;
		float newAngle = 0;
		if (isOver() == -1)
			newAngle = (float)(rand() % 1100) / 1000;
		if (isOver() == 1)
			newAngle = (PI - (float)(rand() % 1100) / 1000);
		ball.setSpeed(400);
		ball.setPosition(this->stateData->gfxSettings->resolution.width / 2, this->stateData->gfxSettings->resolution.height / 2);
		sf::Vector2f ballMovement(0, 0);
		ball.setAngle(newAngle);
		sf::Vector2f direction(cos(ball.getAngle()), sin(ball.getAngle()));
		ballMovement += direction * ball.getSpeed();
		ball.move(ballMovement * dt);
	}
}

void GameState::handleInput(sf::Keyboard::Key k, bool isPressed)
{
	
	if (k == sf::Keyboard::W)
		p1.setIsUp(isPressed);
	if (k == sf::Keyboard::S)
		p1.setIsDown(isPressed);
	if (k == sf::Keyboard::Up)
		p2.setIsUp(isPressed);
	if (k == sf::Keyboard::Down)
		p2.setIsDown(isPressed);
	/*if (k == sf::Keyboard::Escape && isPressed && !checkFinish()) {
		if (isPause == 1)
			text.setString("");
		else
			text.setString("PAUSED");
		isPause = 1 - isPause;
	}*/
	if (k == sf::Keyboard::Enter && isPressed && checkFinish()) {
		text.setString("");
		resetStat(TimePerFrame.asSeconds());
		pointP1 = 0;
		pointP2 = 0;
		convertToText();
	}
}
