#pragma once

#include <memory>
#include <string>
#include<SFML/Graphics.hpp>

#include"StateMachine.h"
#include"AssetManager.h"
#include"InputManager.h"

namespace Khang
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow wwindow;
		AssetManager asset;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class App
	{
	public:
		App(int width, int heigh, std::string title);
	//private:
		
	};
}

