#include "DebugRect.h"

DebugRect::DebugRect(float posX, float posY, float width, float height, sf::Color color) : m_Width(width), m_Height(height), m_Color(color)
, m_PosX(posX), m_PosY(posY), m_Rotation(0)
{
	m_Shape = sf::RectangleShape(sf::Vector2f(m_Width, m_Height));
	m_Shape.setPosition(posX, posY);
	m_Shape.setFillColor(m_Color);
}

void DebugRect::setPosition(float posX, float posY)
{
	m_PosX = posX;
	m_PosY = posY;
	m_Shape.setPosition(m_PosX, m_PosY);
}

void DebugRect::setSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
	m_Shape.setSize(sf::Vector2f(m_Width, m_Height));
}

sf::Color DebugRect::getColor() const
{
	return m_Color;
}

void DebugRect::setColor(sf::Color color)
{
	m_Color = color;
	m_Shape.setFillColor(m_Color);
}

void DebugRect::setRotation(float rotation)
{
	m_Rotation = rotation;
	m_Shape.setOrigin(m_Width / 2, m_Height / 2);
	m_Shape.setRotation(m_Rotation);
	m_Shape.setPosition(m_PosX + m_Width/2, m_PosY + m_Height/2);
}

void DebugRect::draw(sf::RenderWindow& window)
{
	window.draw(m_Shape);
}