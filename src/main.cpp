#include <SFML/Graphics.hpp>
#include "ball.h"
#include "bouncePad.h"
#include "brick.h"
#include "direction.h"

#include <vector>
#include <fstream>

// Initialize Window
sf::Vector2f viewSize(840, 1440);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "Breakout", sf::Style::Default);

// Global Declarations
Direction getLaunchAngle();
bool checkCollision(sf::FloatRect shape1, sf::FloatRect shape2);
void resetBall();
void reset();

// Textures

// Player
BouncePad bouncePad;
sf::Vector2f padPosition;
//bool padMoving = false;

// Ball
Ball ball;

// Bricks
//std::vector<Brick*> bricks;

// Global Variables
float currentTime;
float prevTime = 0.0f;
int score = 0;
bool gameover = true;
int lives = 1;

// Text

// Audio

void init() {
	srand((int)time(0));

	Direction launchDirection = getLaunchAngle();

	bouncePad.init(sf::Vector2f(100.f, 20.f), sf::Vector2f(viewSize.x * 0.5f - 50.0f, viewSize.y * 0.75f), sf::Color::White);
	ball.init(25, sf::Vector2f(viewSize.x * 0.5f - 25, viewSize.y * 0.75f - 150.0f), launchDirection, sf::Color::White);
}

void draw() {
	window.draw(bouncePad.getShape());
	window.draw(ball.getShape());
}

void updateInput() {
    sf::Event event;

    while (window.pollEvent(event)) {

		// check for start event
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {
				if (gameover) {
					gameover = false;
					reset();
				}
			}
		}

		// check for exit events
		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
			window.close();
		}
	}

	// check game events and move bouncePad
	float padAcceleration = 0.0f;
	const float dAcc = 1.1f;

	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		padAcceleration -= dAcc;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		padAcceleration += dAcc;
	}
        
    bouncePad.move(padAcceleration);

}

void update(float dt) {
	bouncePad.update(dt);
	ball.update(dt);

	// Check Collision Between Paddle
	if (checkCollision(bouncePad.getGlobalBounds(), ball.getGlobalBounds())) {
		ball.bounce(1);
	}
	
	// Update Position
	if (ball.getShape().getPosition().x >= 820 - (ball.getShape().getRadius() * 2)) {
		ball.getShape().setPosition(sf::Vector2f(820 - (ball.getShape().getRadius() * 2), 
														ball.getShape().getPosition().y));
		ball.bounce(2);
	}
	else if (ball.getShape().getPosition().x <= 20) {
		ball.getShape().setPosition(20, ball.getShape().getPosition().y);
		ball.bounce(2);
	} else if (ball.getShape().getPosition().y <= 20) {
		ball.getShape().setPosition(ball.getShape().getPosition().x, 20);
		ball.bounce(1);
	}
	

	// Update Lives
	Direction newLaunchDirection = getLaunchAngle();
	if (ball.getShape().getPosition().y >= 1440 - 75.0f) {
		gameover = true;
		ball.reset(viewSize, newLaunchDirection);
		lives--;
	}

	currentTime += dt;
}

int main()
{
    sf::Clock clock;
	window.setFramerateLimit(60);
	init();
	while (window.isOpen()) {
		if (gameover && lives != 0) { init(); }
		// Update input
		updateInput();
		// Update Game
		sf::Time dt = clock.restart();
		if (!gameover) {
			update(dt.asSeconds());
		}
		// Draw
		window.clear(sf::Color::Black);
		draw();

		// Show
		window.display();

		
	}
	return 0;
}

Direction getLaunchAngle() {
	const float pi = 3.1415;

	Direction launch;

	int quadrant = 1 + (rand() % 2);

	int speed = 600;

	float angle = 1 + (rand() % 60) + 15;
	float rad = angle * (pi / 180);

	switch (quadrant)
	{
	case 1:
		// Left
		launch._vX = speed * cos(rad);
		launch._vY = speed * -sin(rad);
		break;
	case 2:
		// Right
		launch._vX = speed * -cos(rad);
		launch._vY = speed * -sin(rad);
		break;
	default:
		break;
	}

	return launch;
}

bool checkCollision(sf::FloatRect shape1, sf::FloatRect shape2) {
	if (shape1.intersects(shape2)) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

void resetBall() {
	ball.getShape().setPosition(sf::Vector2f(viewSize.x * 0.5f + 25, viewSize.y * 0.75f - 150.0f));
}

void reset() {
	lives = 3;
	currentTime = 0.0f;
	prevTime = 0.0f;
}