#include "Player.h"

void Player::init()
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\tile_0007.png"))
	{
		std::cout << "Error loading sprite from file for player" << std::endl;
	}
	m_body.setTexture(m_texture);
	m_body.setScale(sf::Vector2f(4.0f, 4.0f));
	m_body.setPosition(sf::Vector2f(400, 300));

	int min = -100;
	int max = 100;

	m_velocity = sf::Vector2f(min + (std::rand() % (max - min + 1)), min + (std::rand() % (max - min + 1)));
}

void Player::processOutOfBounds()
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

void Player::processMaxSpeed()
{
	if (m_velocity.x > 300.0f)
	{
		m_velocity.x = 300.0f;
	}
	else if (m_velocity.x < -300.0f)
	{
		m_velocity.x = -300.0f;
	}

	if (m_velocity.y > 300.0f)
	{
		m_velocity.y = 300.0f;
	}
	else if (m_velocity.y < -300.0f)
	{
		m_velocity.y = -300.0f;
	}
}

Player::Player()
{
	init();
}

void Player::update(sf::Time t_deltaTime)
{
	processMaxSpeed();


	m_body.move(m_velocity * t_deltaTime.asSeconds());

	processOutOfBounds();
}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}

void Player::processEvents(sf::Event t_event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_velocity.x == 0.0f)
		{
			int min = -100;
			int max = 100;

			m_velocity = sf::Vector2f(min + (std::rand() % (max - min + 1)), min + (std::rand() % (max - min + 1)));
		}
		m_velocity.x *= 1.10;
		m_velocity.y *= 1.10;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_velocity.x == 0.0f)
		{
			int min = -100;
			int max = 100;

			m_velocity = sf::Vector2f(min + (std::rand() % (max - min + 1)), min + (std::rand() % (max - min + 1)));
		}

		m_velocity.x *= 0.8;
		m_velocity.y *= 0.8;

		if ((m_velocity.x < 1 && m_velocity.x > 0) || (m_velocity.y < 1 && m_velocity.y > 0))
		{
			m_velocity = sf::Vector2f(0.0f, 0.0f);
		}
		else if ((m_velocity.x > -1 && m_velocity.x < 0) || (m_velocity.y > -1 && m_velocity.y < 0))
		{
			m_velocity = sf::Vector2f(0.0f, 0.0f);
		}
	}
}
