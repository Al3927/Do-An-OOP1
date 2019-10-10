#pragma once
#include <SFML/Graphics.hpp>
class paddle : public sf::RectangleShape
{
private:
	float speed;
	bool isUp;
	bool isDown;
public:
	paddle();
	void setIsUp(bool b);
	void setIsDown(bool b);
	bool getIsUp();
	bool getIsDown();
	float getSpeed();
};

