#pragma once
#include <SFML/Graphics.hpp>
class Ball : public sf::CircleShape 
{
private:
	sf::Vector2f angle;	
	float speed;
public:
	Ball();
	sf::Vector2f getAngle();
	float getSpeed();
	void setAngle(sf::Vector2f a);
};

