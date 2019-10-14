#include "Game.h"

void Game::processEvents() {
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

void Game::update(sf::Time dt) {
  if (isOver()) {
	countPoint();
	if(!checkFinish())
	  resetStat(dt);
  }
  else {
	  updatePlayerMovement(dt);
	  updateBallMovement(dt);
  }
}

void Game::render() {
	window.clear();
	window.draw(text);
	window.draw(instruct);
	window.draw(upperWall);
	window.draw(lowerWall);
	window.draw(ball);
	window.draw(p1);
	window.draw(p2);
	window.draw(tPointP1);
	window.draw(tPointP2);
	window.display();
}

Game::Game() {
  isPause = 0;
  srand(time(NULL));
  font.loadFromFile("arial.ttf");
  tPointP1.setFont(font);
  tPointP2.setFont(font);
  text.setFont(font);
  tPointP1.setString("0");
  tPointP2.setString("0");
  text.setString("");  
  instruct.setString("Score 10 points first to win");
  instruct.setFillColor(sf::Color::White);
  instruct.setFont(font);
  instruct.setCharacterSize(20);
  instruct.setPosition(200, 50);
  text.setCharacterSize(30);
  tPointP1.setCharacterSize(30);
  tPointP2.setCharacterSize(30);
  text.setFillColor(sf::Color::Red);
  tPointP1.setFillColor(sf::Color::Red);
  tPointP2.setFillColor(sf::Color::Red);
  text.setPosition(150, 200);
  tPointP1.setPosition(50, 50);
  tPointP2.setPosition(560, 50);

  pointP1 = 0;
  pointP2 = 0;
  window.create(sf::VideoMode(WIDTH, HEIGHT), "Pong Game");
  p1.setPosition(10, (HEIGHT - p1.getSize().y) / 2);
  p1.setFillColor(sf::Color::Green);
  p2.setPosition(WIDTH - (10 + p2.getSize().x), (HEIGHT - p2.getSize().y) / 2);
  p2.setFillColor(sf::Color::Blue);
  ball.setPosition(WIDTH / 2, HEIGHT / 2);
  upperWall.setSize(sf::Vector2f(WIDTH, WALL_THICKNESS));
  upperWall.setPosition(0, 0);
  upperWall.setFillColor(sf::Color::Cyan);
  lowerWall.setSize(sf::Vector2f(WIDTH, WALL_THICKNESS));
  lowerWall.setPosition(0, HEIGHT - WALL_THICKNESS);
  lowerWall.setFillColor(sf::Color::Cyan);
}

Game::~Game() = default;

int Game::isOver() {
  if (ball.getPosition().x + ball.getRadius() <= 0)
	return 1;
  if (ball.getPosition().x - ball.getRadius() > WIDTH)
	return -1;
  else return 0;
}

bool Game::isCollisionWithP1() {
  return (ball.getPosition().x - ball.getRadius() <= p1.getPosition().x + p1.getSize().x &&
		  //ball.getPosition().x - ball.getRadius() >= p1.getPosition().x &&
		  ball.getPosition().y >= p1.getPosition().y &&
		  ball.getPosition().y <= p1.getPosition().y + p1.getSize().y);
}

bool Game::isCollisionWithP2() {
  return (//ball.getPosition().x + ball.getRadius() <= p2.getPosition().x + p2.getSize().x &&
		  ball.getPosition().x + ball.getRadius() >= p2.getPosition().x &&
		  ball.getPosition().y >= p2.getPosition().y &&
		  ball.getPosition().y <= p2.getPosition().y + p2.getSize().y);
}

bool Game::isCollisionWithWalls() {
  return (ball.getPosition().y - ball.getRadius() <= WALL_THICKNESS || ball.getPosition().y + ball.getRadius() >= HEIGHT - WALL_THICKNESS);
}

void Game::updatePlayerMovement(sf::Time dt) {
  sf::Vector2f p1Movement(0, 0);
  sf::Vector2f p2Movement(0, 0);
  if (p1.getIsUp() && p1.getPosition().y >= WALL_THICKNESS)
	p1Movement.y -= p1.getSpeed();
  if (p1.getIsDown() && p1.getPosition().y <= HEIGHT - p1.getSize().y - WALL_THICKNESS)
	p1Movement.y += p1.getSpeed();
  if (p2.getIsUp() && p2.getPosition().y >= WALL_THICKNESS)
	p2Movement.y -= p2.getSpeed();
  if (p2.getIsDown() && p2.getPosition().y <= HEIGHT - p1.getSize().y - WALL_THICKNESS)
	p2Movement.y += p2.getSpeed();
  p1.move(p1Movement * dt.asSeconds());
  p2.move(p2Movement * dt.asSeconds());
}

void Game::updateBallMovement(sf::Time dt) {
  sf::Vector2f ballMovement(0, 0);
  float phi = ball.getAngle();
  float newAngle = phi;
  if (isCollisionWithWalls()) 
	newAngle = -phi;
  if (isCollisionWithP1()) {
	if (phi > 0)
	  newAngle = (float)(rand() % 1100) / 1000;
	else
	  newAngle = -(float)(rand() % 1100) / 1000;
	ball.setSpeed(ball.getSpeed()*1.1);
  }
	
  if (isCollisionWithP2()) {
	if (phi > 0)
	  newAngle = (PI - (float)(rand() % 1100) / 1000);
	else
	  newAngle = -(PI - (float)(rand() % 1100) / 1000);
	ball.setSpeed(ball.getSpeed()*1.1);
  }
  ball.setAngle(newAngle);
  sf::Vector2f direction(cos(ball.getAngle()), sin(ball.getAngle()));
  ballMovement += direction * ball.getSpeed();
  ball.move(ballMovement * dt.asSeconds());
}

void Game::countPoint() {
  if (!flag) {
	  if (isOver() == -1)
		pointP1++;
	  if (isOver() == 1)
		pointP2++;
	  c.restart();
	flag = true;
	convertToText();
  }
}

bool Game::checkFinish() {
  if (pointP1 == finishPoint || pointP2 == finishPoint) {
	if (pointP1 == finishPoint)
	  text.setString("P1 wins, Enter to play again");
	else
	  text.setString("P2 wins, Enter to play again");
	return true;
  }
  return false;
}

void Game::convertToText() {
  std::string s1;
  std::string s2;
  s1 = std::to_string(pointP1);
  s2 = std::to_string(pointP2);
  tPointP1.setString(s1);
  tPointP2.setString(s2);
}

void Game::resetStat(sf::Time dt) {
  if (c.getElapsedTime() >= DelayTime) {
	flag = false;
	float newAngle = 0;
	if (isOver() == -1)
	  newAngle = (float)(rand() % 1100) / 1000;
	if (isOver() == 1)
	  newAngle = (PI - (float)(rand() % 1100) / 1000);
	ball.setSpeed(400);
	ball.setPosition(WIDTH / 2, HEIGHT / 2);
	sf::Vector2f ballMovement(0, 0);
	ball.setAngle(newAngle);
	sf::Vector2f direction(cos(ball.getAngle()), sin(ball.getAngle()));
	ballMovement += direction * ball.getSpeed();
	ball.move(ballMovement * dt.asSeconds());
  }
}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (window.isOpen()) {
	processEvents();
	timeSinceLastUpdate += clock.restart();
	while (timeSinceLastUpdate > TimePerFrame) {
	  timeSinceLastUpdate -= TimePerFrame;
	  processEvents();
	  if (!isPause && !checkFinish())
		update(TimePerFrame);
	}
	render();
  }
}

void Game::handleInput(sf::Keyboard::Key k, bool isPressed) {
  if (k == sf::Keyboard::W)
	p1.setIsUp(isPressed);
  if (k == sf::Keyboard::S)
	p1.setIsDown(isPressed);
  if (k == sf::Keyboard::Up)
	p2.setIsUp(isPressed);
  if (k == sf::Keyboard::Down)
	p2.setIsDown(isPressed);
  if (k == sf::Keyboard::Escape && isPressed && !checkFinish()) {
	if (isPause == 1)
	  text.setString("");
	else
	  text.setString("PAUSED");
	isPause = 1 - isPause;
  }
  if (k == sf::Keyboard::Enter && isPressed && checkFinish()) {
	text.setString("");
	resetStat(TimePerFrame);
	pointP1 = 0;
	pointP2 = 0;
	convertToText();
  }
}
