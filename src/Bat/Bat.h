#pragma once
#include <SFML/Graphics.hpp>

class Bat
{
private:
	sf::Vector2f m_position;
	
	sf::RectangleShape m_shape;

	float m_speed{ 1000.0f };

	bool m_movingRight{ false };
	bool m_movingLeft{ false };
public:
	Bat(float startX, float startY);

	sf::FloatRect getPosition();
	sf::RectangleShape getShape();

	void moveLeft();
	void moveRight();

	void stopLeft();
	void stopRight();

	void update(sf::Time dt);
};