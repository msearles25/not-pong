#include "Bat.h"

// The constructor, which is call when the an object is created
Bat::Bat(float startX, float startY)
{
	m_position.x = startX;
	m_position.y = startY;

	m_shape.setSize(sf::Vector2f(50, 5));
	m_shape.setPosition(m_position);
}

sf::FloatRect Bat::getPosition()
{
	return m_shape.getGlobalBounds();
}

sf::RectangleShape Bat::getShape()
{
	return m_shape;
}

void Bat::moveLeft()
{
	m_movingLeft = true;
}

void Bat::moveRight()
{
	m_movingRight = true;
}

void Bat::stopLeft()
{
	m_movingLeft = false;
}

void Bat::stopRight()
{
	m_movingRight = false;
}

void Bat::update(sf::Time dt)
{
	if (m_movingLeft)
	{
		m_position.x -= m_speed * dt.asSeconds();
	}
	
	if (m_movingRight)
	{
		m_position.x += m_speed * dt.asSeconds();
	}

	m_shape.setPosition(m_position);
}