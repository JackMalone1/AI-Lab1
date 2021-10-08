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
	m_body.setOrigin(m_body.getGlobalBounds().width / 2.0f, m_body.getGlobalBounds().height / 2.0f);
	m_body.setRotation(90.0f);

	m_acceleration = 10.0f;
	m_speed = 0.0f;
	m_rotationSpeed = 5.0f;
	m_maxSpeed = 10.0f;
	m_minSpeed = -5.0f;
	
	m_velocity = sf::Vector2f(0.0f, 0.0f);
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
	if (m_speed > m_maxSpeed) m_speed = m_maxSpeed;
	if (m_speed < m_minSpeed) m_speed = m_minSpeed;
}

void Player::resetVelocity()
{
	int min = -100;
	int max = 100;

	m_velocity = sf::Vector2f(min + (std::rand() % (max - min + 1)), min + (std::rand() % (max - min + 1)));
}

void Player::stopPlayer()
{
	if ((m_velocity.x < 1 && m_velocity.x > 0) || (m_velocity.y < 1 && m_velocity.y > 0))
	{
		m_velocity = sf::Vector2f(0.0f, 0.0f);
	}
	else if ((m_velocity.x > -1 && m_velocity.x < 0) || (m_velocity.y > -1 && m_velocity.y < 0))
	{
		m_velocity = sf::Vector2f(0.0f, 0.0f);
	}
}

Player::Player()
{
	init();
}

void Player::update(sf::Time t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_speed += m_acceleration * t_deltaTime.asSeconds();
		processMaxSpeed();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_speed -= m_acceleration * t_deltaTime.asSeconds();
		processMaxSpeed();
		//stopPlayer();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_body.setRotation(m_body.getRotation() - m_speed * m_rotationSpeed * t_deltaTime.asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_body.setRotation(m_body.getRotation() + m_speed * m_rotationSpeed * t_deltaTime.asSeconds());
	}

	m_direction.x = cosf(m_body.getRotation() * (3.14f / 180.0f));
	m_direction.y = sinf(m_body.getRotation() * (3.14f / 180.0f));
	m_velocity = sf::Vector2f((m_direction.x * m_speed ), (m_direction.y * m_speed));


	m_body.move(m_velocity);

	processOutOfBounds();
}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}
