#include "bouncePad.h"

BouncePad::BouncePad() {}

BouncePad::~BouncePad() {}

void BouncePad::init(sf::Vector2f size, sf::Vector2f position, sf::Color color) {

    m_shape.setSize(size);
    m_position = position;
    m_shape.setPosition(m_position);
    m_shape.setFillColor(color);
    
}

void BouncePad::update(float dt) {

    if (m_position.x >= 820 - m_shape.getSize().x) {
        m_position.x = 820 - m_shape.getSize().x;
        m_velocity = 0;
    }
    if (m_position.x <= 20) {
        m_position.x = 20;
        m_velocity = 0;
    }
}

void BouncePad::move(float acceleration) {
    m_velocity += acceleration;
    m_position.x += m_velocity;
    m_velocity = 0.95f * m_velocity;
    acceleration = 0;
    m_shape.setPosition(m_position);
}


sf::FloatRect BouncePad::getGlobalBounds() {
    return m_shape.getGlobalBounds();
}

sf::RectangleShape BouncePad::getShape() {
    return m_shape;
}

float BouncePad::getVelocity() {
    return m_velocity;
}