#include "Ball.h"

Ball::Ball()
{
	setRadius(10);
	setOrigin(getRadius(), getRadius());
	setFillColor(sf::Color::White);
	speed = 400;
	angle = -PI;
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

void Ball::setSpeed(float s) {
  speed = s;
}
