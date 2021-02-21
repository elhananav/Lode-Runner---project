#include "text.h"

text::text(const sf::Font& font)
{
	m_text.setFont(font);
}//end text constructor

void text::draw(sf::RenderWindow& window) const
{
	window.draw(m_text);
}//end draw

void text::setColor(const sf::Color& color)
{
	m_text.setColor(color);
}//end setColor

void text::setText(std::string str)
{
	m_text.setString(str);
	m_text.setOutlineThickness(3);
	m_text.setOutlineColor(sf::Color::Black);
}//end setText

void text::setPosition(const sf::Vector2f& location)
{
	m_text.setPosition(location);
}//end setPosition

void text::setCharacterSize(int size)//change text size
{
	m_text.setCharacterSize(size);
}//end setCharacterSize

