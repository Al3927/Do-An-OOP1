#include "paddle.h"

paddle::paddle()
{
	setSize(sf::Vector2f(20, 80));
	speed = 400;
	isUp = 0; 
	isDown = 0;
}

void paddle::setIsUp(bool b)
{
	isUp = b;
}

void paddle::setIsDown(bool b)
{
	isDown = b;
}

bool paddle::getIsUp()
{
	return isUp;
}

bool paddle::getIsDown()
{
	return isDown;
}

float paddle::getSpeed()
{
	return speed;
}
