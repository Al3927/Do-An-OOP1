#include "Game.h"

void Game::processEvents()
{
	sf::Event e;
	while (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed)
			window.close();
	}
}

void Game::update(sf::Time dt)
{
	sf::FloatRect boundingBox = ball.getGlobalBounds();
	sf::FloatRect upWall = upperWall.getGlobalBounds();
	sf::FloatRect lowWall = lowerWall.getGlobalBounds();
	sf::FloatRect lWall = leftWall.getGlobalBounds();
	sf::FloatRect rWall = rightWall.getGlobalBounds();
	sf::Vector2f movement(0, 0);
	sf::Vector2f pos = ball.getPosition();
	if (boundingBox.intersects(upWall) || boundingBox.intersects(lowWall)) {
		sf::Vector2f newAngle(ball.getAngle().x, (-1) * ball.getAngle().y);
		ball.setAngle(newAngle);
	}
	if (boundingBox.intersects(rWall) || boundingBox.intersects(lWall)) {
		sf::Vector2f newAngle((-1) * ball.getAngle().x, ball.getAngle().y);
		ball.setAngle(newAngle);
	}
	movement += ball.getAngle() * ball.getSpeed();
	ball.move(movement * dt.asSeconds());
}

void Game::render()
{
	window.clear();
	window.draw(upperWall);
	window.draw(lowerWall);
	window.draw(leftWall);
	window.draw(rightWall);
	window.draw(ball);
	window.display();
}

Game::Game()
{
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Pong Game");
	upperWall.setSize(sf::Vector2f(WIDTH, WALL_THICKNESS));
	upperWall.setPosition(0, 0);
	upperWall.setFillColor(sf::Color::Cyan);
	lowerWall.setSize(sf::Vector2f(WIDTH, WALL_THICKNESS));
	lowerWall.setPosition(0, HEIGHT - WALL_THICKNESS);
	lowerWall.setFillColor(sf::Color::Cyan);
	leftWall.setSize(sf::Vector2f(WALL_THICKNESS, HEIGHT));
	leftWall.setPosition(0, 0);
	leftWall.setFillColor(sf::Color::Cyan);
	rightWall.setSize(sf::Vector2f(WALL_THICKNESS, HEIGHT));
	rightWall.setPosition(WIDTH - WALL_THICKNESS, 0);
	rightWall.setFillColor(sf::Color::Cyan);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}
