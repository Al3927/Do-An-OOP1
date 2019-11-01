#pragma once
#include "stdafx.h"
#include "GameState.h"
class GameSingleState :
	public GameState
{
public:
	GameSingleState(StateData* state_data);
	virtual ~GameSingleState();
	void updatePlayerMovement(const float& dt);
	void updatePauseMenuButtons();
	void handleInput(sf::Keyboard::Key k, bool isPressed);
private:
};

