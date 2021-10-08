#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

class Npc
{
private:
	sf::Sprite m_body;
	sf::Texture m_texture;

	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;

	float minSpeed = 1;
	float maxSpeed = 4;
	float speed;
	float acceleration;
	float rotationSpeed;
	float arrivalRadius = 10;
	float targetSpeed = 0;

	void init();
	void processOutOfBounds();

	sf::Vector2f normaliseVector(sf::Vector2f t_inputVector);
public:
	Npc();
	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& t_window);
	void kinematicSeek(sf::Vector2f t_targetPosition);
	void kinematicArrive(sf::Vector2f t_targetPosition);
	void kinematicWander();
	void kinematicFlee(sf::Vector2f t_fleePosition);
};

