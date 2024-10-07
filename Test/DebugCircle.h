#pragma once
#include "SFML/Graphics.hpp"

class DebugCircle
{
public:
	DebugCircle(float posX, float posY, float radius, sf::Color color);
	float getRadius() const;
	void setRadius(float radius);
	sf::Color getColor() const;
	void setColor(sf::Color color);
	void setPosition(float posX, float posY);

	void draw(sf::RenderWindow& window);

private:
	sf::CircleShape m_Shape;
	sf::Color m_Color;
	float m_Radius;
};