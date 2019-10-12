#pragma once
#include <SFML/Graphics.hpp>
const float PI = 3.1415f;
class Ball : public sf::CircleShape 
{
private:
	float angle;	
	float speed;
public:
	Ball();
	float getAngle();
	float getSpeed();
	void setAngle(float a);
	void setSpeed(float s);
};

