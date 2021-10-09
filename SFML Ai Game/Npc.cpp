#include "Npc.h"

void Npc::init()
{
	setUpSprites();

	m_velocity = sf::Vector2f(0.0f, 0.0f);
	speed = 4.0f;

	if (wander) kinematicWander();
}

void Npc::setUpSprites()
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\tile_0008.png"))
	{
		std::cout << "Error loading sprite from file for npc" << std::endl;
	}
	m_body.setTexture(m_texture);
	m_body.setScale(sf::Vector2f(4.0f, 4.0f));
	m_body.setPosition(sf::Vector2f(200, 150));
	m_body.setOrigin(m_body.getGlobalBounds().width / 2.0f, m_body.getGlobalBounds().height / 2.0f);
}

void Npc::processOutOfBounds()
{
	if (m_body.getPosition().x + m_body.getGlobalBounds().width > 800)
	{
		m_body.setPosition(m_body.getGlobalBounds().width + 10, m_body.getPosition().y);
	}
	else if (m_body.getPosition().x - m_body.getGlobalBounds().width < 0)
	{
		m_body.setPosition(800 - m_body.getGlobalBounds().width, m_body.getPosition().y);
	}

	if (m_body.getPosition().y - m_body.getGlobalBounds().height > 600)
	{
		m_body.setPosition(m_body.getPosition().x, m_body.getGlobalBounds().height);
	}
	else if (m_body.getPosition().y + m_body.getGlobalBounds().height < 0)
	{
		m_body.setPosition(m_body.getPosition().x, 600 - m_body.getGlobalBounds().height);
	}
}

sf::Vector2f Npc::normaliseVector(sf::Vector2f t_inputVector)
{
	sf::Vector2f result = sf::Vector2f(0.0f, 0.0f);
	result = t_inputVector / sqrt((t_inputVector.x * t_inputVector.x) + (t_inputVector.y * t_inputVector.y));
	return result;
}

Npc::Npc(int t_type)
{
	switch (t_type)
	{
	case 1:
		wander = true;
	case 2:
		seek = true;
	case 3:
		flee = true;
	default:
		break;
	}


	init();
}

void Npc::update(sf::Time t_deltaTime)
{
	if (wander)
	{
		if (timer.getElapsedTime().asSeconds() > 2)
		{
			kinematicWander();
			timer.restart();
		}
	}

	m_body.move(m_velocity * t_deltaTime.asSeconds());

	processOutOfBounds();
}

void Npc::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}

void Npc::kinematicSeek(sf::Vector2f t_targetPosition)
{
	if (t_targetPosition != m_body.getPosition())
	{
		sf::Vector2f steeringLinear = t_targetPosition - m_body.getPosition();
		steeringLinear = normaliseVector(steeringLinear);
		steeringLinear *= maxSpeed;
		m_velocity = steeringLinear;
		m_body.setRotation(atan2f(steeringLinear.y, steeringLinear.x) * (180.0f / 3.14f));
	}
}

void Npc::kinematicArrive(sf::Vector2f t_targetPosition)
{
	if (t_targetPosition != m_body.getPosition())
	{
		sf::Vector2f steeringLinear = t_targetPosition - m_body.getPosition();
		float magnitude = sqrt((steeringLinear.x * steeringLinear.x) + (steeringLinear.y * steeringLinear.y));
		if (magnitude < arrivalRadius)
		{
			speed = 0;
		}
		else if (magnitude > 8)
		{
			speed = maxSpeed;
		}
		else
		{
			speed = maxSpeed * (magnitude / 8);
		}
		m_velocity = steeringLinear;
		m_velocity = normaliseVector(m_velocity);
		m_velocity *= maxSpeed;
	}
}

void Npc::kinematicWander()
{
	float rotationChange = rand() % 40 - 20;
	float rotation = m_body.getRotation() + rotationChange;

	m_direction.x = cosf(rotation * (3.14f / 180.0f));
	m_direction.y = sinf(rotation * (3.14f / 180.0f));
	m_velocity = sf::Vector2f((m_direction.x * speed), (m_direction.y * speed));
	m_body.setRotation(rotation);
}

void Npc::kinematicFlee(sf::Vector2f t_fleePosition)
{
	if (t_fleePosition != m_body.getPosition())
	{
		sf::Vector2f steeringLinear = t_fleePosition - m_body.getPosition();
		steeringLinear = normaliseVector(steeringLinear);
		steeringLinear *= maxSpeed;
		m_velocity = steeringLinear;
	}
}
