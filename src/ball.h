#pragma once

#include <SFML/Graphics.hpp>
#include "direction.h"


class Ball
{
public:
	Ball();
	~Ball();
	void init(float radius, sf::Vector2f position, Direction direction, sf::Color color);
	void update(float dt);
	void bounce(int direction);
	sf::FloatRect getGlobalBounds();
	sf::CircleShape getShape();
	void reset(sf::Vector2f viewSize, Direction Direction);
private:
	sf::Vector2f m_position;
	sf::CircleShape m_shape;
	Direction m_direction;
	float m_speed;
};