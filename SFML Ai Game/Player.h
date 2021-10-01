#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
class Player
{
private:
	sf::Sprite m_body;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;

	void init();
	void processOutOfBounds();
	void processMaxSpeed();
public:
	Player();
	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& t_window);
	void processEvents(sf::Event t_event);
};

