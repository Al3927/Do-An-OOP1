#include "Ball.h"

Ball::Ball()
{
	setRadius(20);
	setPosition(100, 100);
	setFillColor(sf::Color::Red);
	speed = 100;
	angle.x = 0.25;
	angle.y = 1;
}


sf::Vector2f Ball::getAngle()
{
	return angle;
}

float Ball::getSpeed()
{
	return speed;
}

void Ball::setAngle(sf::Vector2f a) {
	angle = a;
}