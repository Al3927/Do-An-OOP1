#include "stdafx.h"
#include "paddle.h"

paddle::paddle()
{
	setSize(sf::Vector2f(10, 100));
	speed = 500;
	isUp = 0;
	isDown = 0;
}

paddle::~paddle()
{
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


