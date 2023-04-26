#pragma once

#include <SFML/Graphics.hpp>

class Brick
{
    public:
        Brick();
	    ~Brick();

	    void init(std::string textureName, sf::Vector2f position);
	    void update(float dt);
    	sf::Sprite getSprite();
    private:
        sf::Texture m_texture;
	    sf::Sprite m_sprite;
	    sf::Vector2f m_position;
	    sf::Vector2i m_spriteSize;

        bool broken;
};