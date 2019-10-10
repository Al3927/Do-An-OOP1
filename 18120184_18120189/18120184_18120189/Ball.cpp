#include "Ball.h"

Ball::Ball()
{
	setRadius(10);
	setFillColor(sf::Color::Red);
	speed = 400;
	angle = -2*PI/3;
}


float Ball::getAngle()
{
	return angle;
}

float Ball::getSpeed()
{
	return speed;
}

void Ball::setAngle(float a) {
	angle = a;
}