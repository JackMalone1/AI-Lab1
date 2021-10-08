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
	sf::Vector2f m_direction;

	float m_acceleration;
	float m_speed;
	float m_maxSpeed;
	float m_minSpeed;
	float m_rotationSpeed;

	void init();
	void processOutOfBounds();
	void processMaxSpeed();
	void resetVelocity();
	void stopPlayer();
public:
	Player();
	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& t_window);
	void processEvents(sf::Event t_event);
	sf::Vector2f getPosition() { return m_body.getPosition(); }
};

