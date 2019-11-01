#include "GameSingleState.h"

GameSingleState::GameSingleState(StateData* state_data) : GameState(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initvari();
	this->initPauseMenu();

	//Tran Dang Khoa


}

GameSingleState::~GameSingleState()
{
}

void GameSingleState::updatePlayerMovement(const float& dt)
{
	sf::Vector2f p1Movement(0, 0);
	sf::Vector2f p2Movement(0, 0);
	if (p1.getIsUp() && p1.getPosition().y >= WALL_THICKNESS)
		p1Movement.y -= p1.getSpeed();
	if (p1.getIsDown() && p1.getPosition().y <= this->stateData->gfxSettings->resolution.height - p1.getSize().y - WALL_THICKNESS)
		p1Movement.y += p1.getSpeed();
	if (p2.getPosition().y + (p2.getSize().y / 2) > ball.getPosition().y&& p2.getPosition().y >= WALL_THICKNESS)
		p2Movement.y -= p2.getSpeed();
	if (p2.getPosition().y + (p2.getSize().y / 2) < ball.getPosition().y && p2.getPosition().y <= this->stateData->gfxSettings->resolution.height - p1.getSize().y - WALL_THICKNESS)
		p2Movement.y += p2.getSpeed();

	p1.move(p1Movement * dt);
	p2.move(p2Movement * dt);
}

void GameSingleState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
	if (this->pmenu->isButtonPressed("SAVE_CASE_1"))
		this->saveGame("case_single_1.txt");
	if (this->pmenu->isButtonPressed("SAVE_CASE_2"))
		this->saveGame("case_single_2.txt");
	if (this->pmenu->isButtonPressed("SAVE_CASE_3"))
		this->saveGame("case_single_3.txt");
	if (this->pmenu->isButtonPressed("LOAD_CASE_1"))
		this->loadGame("case_single_1.txt");
	if (this->pmenu->isButtonPressed("LOAD_CASE_2"))
		this->loadGame("case_single_2.txt");
	if (this->pmenu->isButtonPressed("LOAD_CASE_3"))
		this->loadGame("case_single_3.txt");
}

void GameSingleState::handleInput(sf::Keyboard::Key k, bool isPressed)
{
	if (k == sf::Keyboard::W)
		p1.setIsUp(isPressed);
	if (k == sf::Keyboard::S)
		p1.setIsDown(isPressed);
	/*if (k == sf::Keyboard::Up)
		p2.setIsUp(isPressed);
	if (k == sf::Keyboard::Down)
		p2.setIsDown(isPressed);*/
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
