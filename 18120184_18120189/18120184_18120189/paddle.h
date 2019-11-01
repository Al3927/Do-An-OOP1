#pragma once
#include <SFML/Graphics.hpp>



//class MovementComponent;

class paddle : public sf::RectangleShape
{
private:
	float speed;
	bool isUp;
	bool isDown;
public:
	paddle();
	~paddle();
	void setIsUp(bool b);
	void setIsDown(bool b);
	bool getIsUp();
	bool getIsDown();
	float getSpeed();
	//MovementComponent* movementComponent;
	//void move(const float dir_x, const float dir_y, const float& dt);
	//void stopVelocity();
	//void stopVelocityX();
	//void stopVelocityY();
};

