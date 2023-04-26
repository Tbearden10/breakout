#include "ball.h"

Ball::Ball() {}

Ball::~Ball() {}

void Ball::init(float radius, sf::Vector2f position, Direction direction, sf::Color color) {

	m_position = position;
	m_direction = direction;
	m_shape.setRadius(radius);
	m_shape.setFillColor(color);
	m_shape.setPosition(m_position);

}

void Ball::update(float dt) {
	m_shape.move(m_direction._vX * dt, m_direction._vY * dt);
}

void Ball::bounce(int direction) {
	
	// Up or Down
	if (direction == 1) {
		m_direction._vY = m_direction._vY * -0.99;
	}
	// Left or Right
	if (direction == 2) {
		m_direction._vX = m_direction._vX * -0.99;
	}
	
}
sf::FloatRect Ball::getGlobalBounds() {
	return m_shape.getGlobalBounds();
}

sf::CircleShape Ball::getShape() {
	return m_shape;
}

void Ball::reset(sf::Vector2f viewsize, Direction direction) {
	m_position.x = viewsize.x * 0.5f + 25.0f;
	m_position.y = viewsize.y * 0.75f - 150.0f;

	m_shape.setPosition(sf::Vector2f(m_position.x, m_position.y));

	m_direction._vX = 0;
	m_direction._vY = 0;
}