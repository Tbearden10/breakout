#pragma once

#include <SFML/Graphics.hpp>

class BouncePad 
{
    public:
        BouncePad();
        ~BouncePad();

        void init(sf::Vector2f size, sf::Vector2f position, sf::Color color);
        void update(float dt);
        void move(float acceleration);
        sf::FloatRect getGlobalBounds();
        sf::RectangleShape getShape();
        float getVelocity();

    private:
        sf::Vector2f m_position;
        sf::RectangleShape m_shape;
        float m_velocity;


};