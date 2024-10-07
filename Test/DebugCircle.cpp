#include "DebugCircle.h"

DebugCircle::DebugCircle(float posX, float posY, float radius, sf::Color color) : m_Radius(radius), m_Color(color)
{
	m_Shape = sf::CircleShape(m_Radius);
	m_Shape.setOrigin(m_Radius, m_Radius);
	m_Shape.setFillColor(m_Color);
	m_Shape.setPosition(posX, posY);
}

float DebugCircle::getRadius() const
{
	return m_Radius;
}

void DebugCircle::setRadius(float radius)
{
	m_Radius = radius;
	m_Shape.setOrigin(m_Radius, m_Radius);
}

sf::Color DebugCircle::getColor() const
{
	return m_Color;
}

void DebugCircle::setColor(sf::Color color)
{
	m_Color = color;
	m_Shape.setFillColor(color);
}

void DebugCircle::setPosition(float posX, float posY)
{
	m_Shape.setPosition(posX, posY);
}

void DebugCircle::draw(sf::RenderWindow& window)
{
	window.draw(m_Shape);

}

