#include "Npc.h"

void Npc::init()
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\tile_0008.png"))
	{
		std::cout << "Error loading sprite from file for npc" << std::endl;
	}
	m_body.setTexture(m_texture);
	m_body.setScale(sf::Vector2f(4.0f, 4.0f));
	m_body.setPosition(sf::Vector2f(200, 150));

	int min = -100;
	int max = 100;

	m_velocity = sf::Vector2f(min + (std::rand() % (max - min + 1)), min + (std::rand() % (max - min + 1)));
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

Npc::Npc()
{
	init();
}

void Npc::update(sf::Time t_deltaTime)
{
	m_body.move(m_velocity * t_deltaTime.asSeconds());

	processOutOfBounds();
}

void Npc::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}
