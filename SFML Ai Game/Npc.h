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

	float minSpeed = -5.0f;
	float maxSpeed = 10.0f;
	float speed;
	float acceleration;
	float rotationSpeed;
	float arrivalRadius = 10;
	float targetSpeed = 0;

	void init();
	void setUpSprites();
	void processOutOfBounds();

	sf::Vector2f normaliseVector(sf::Vector2f t_inputVector);

	bool wander = false;
	bool seek = false;
	bool flee = false;

	sf::Clock timer;
public:
	Npc(int t_type);
	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& t_window);
	void kinematicSeek(sf::Vector2f t_targetPosition);
	void kinematicArrive(sf::Vector2f t_targetPosition);
	void kinematicWander();
	void kinematicFlee(sf::Vector2f t_fleePosition);
};

