#include "Game.h"

void Game::processEvents()
{
	sf::Event e;
	while (window.pollEvent(e)) {
		switch (e.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			handleInput(e.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleInput(e.key.code, false);
			break;
		}
	}
}

void Game::update(sf::Time dt)
{
	sf::FloatRect ballBox = ball.getGlobalBounds();
	sf::FloatRect upWall = upperWall.getGlobalBounds();
	sf::FloatRect lowWall = lowerWall.getGlobalBounds();
	sf::FloatRect p1Bound = p1.getGlobalBounds();
	sf::FloatRect p2Bound = p2.getGlobalBounds();

	sf::Vector2f ballMovement(0, 0);
	sf::Vector2f p1Movement(0, 0);
	sf::Vector2f p2Movement(0, 0);

	if (ballBox.intersects(upWall) || ballBox.intersects(lowWall)) 
		ball.setAngle(-ball.getAngle());
	if (ballBox.intersects(p1Bound) || ballBox.intersects(p2Bound))
		ball.setAngle(PI - ball.getAngle());

	sf::Vector2f direction(cos(ball.getAngle()), sin(ball.getAngle()));
	ballMovement += direction * ball.getSpeed();

	if (p1.getIsUp() && p1.getPosition().y >= 0 + WALL_THICKNESS)
		p1Movement.y -= p1.getSpeed();
	if (p1.getIsDown() && p1.getPosition().y <= HEIGHT - 80 - WALL_THICKNESS)
		p1Movement.y += p1.getSpeed();
	if (p2.getIsUp() && p2.getPosition().y >= 0 + WALL_THICKNESS)
		p2Movement.y -= p2.getSpeed();
	if (p2.getIsDown() && p2.getPosition().y <= HEIGHT - 80 - WALL_THICKNESS)
		p2Movement.y += p2.getSpeed();

	p1.move(p1Movement * dt.asSeconds());
	p2.move(p2Movement * dt.asSeconds());
	ball.move(ballMovement * dt.asSeconds());
}

void Game::render()
{
	window.clear();
	window.draw(upperWall);
	window.draw(lowerWall);
	window.draw(ball);
	window.draw(p1);
	window.draw(p2);
	window.display();
}

Game::Game()
{
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Pong Game");
	p1.setPosition(WALL_THICKNESS, (HEIGHT - p1.getSize().y)/2);
	p1.setFillColor(sf::Color::Green);
	p2.setPosition(WIDTH - 2*WALL_THICKNESS, (HEIGHT - p2.getSize().y)/2);
	p2.setFillColor(sf::Color::Blue);
	ball.setPosition(WIDTH / 2, HEIGHT / 2);
	upperWall.setSize(sf::Vector2f(WIDTH, WALL_THICKNESS));
	upperWall.setPosition(0, 0);
	upperWall.setFillColor(sf::Color::Cyan);
	lowerWall.setSize(sf::Vector2f(WIDTH, WALL_THICKNESS));
	lowerWall.setPosition(0, HEIGHT - WALL_THICKNESS);
	lowerWall.setFillColor(sf::Color::Cyan);
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

void Game::handleInput(sf::Keyboard::Key k, bool isPressed)
{
	if (k == sf::Keyboard::W)
		p1.setIsUp(isPressed);
	if (k == sf::Keyboard::S)
		p1.setIsDown(isPressed);
	if (k == sf::Keyboard::Up)
		p2.setIsUp(isPressed);
	if (k == sf::Keyboard::Down)
		p2.setIsDown(isPressed);
}
