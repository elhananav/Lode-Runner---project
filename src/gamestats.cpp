#include "gamestats.h"

const sf::Vector2f startPos(200, 755);//start position of the game state data

gamestats::gamestats(const sf::Font& font)
	:m_level(font), m_life(font), m_score(font), m_time(font)
{
	m_level.setPosition(sf::Vector2f(startPos.x, startPos.y));
	m_life.setPosition(sf::Vector2f(startPos.x * 2, startPos.y));
	m_score.setPosition(sf::Vector2f(startPos.x * 3, startPos.y));
	m_time.setPosition(sf::Vector2f(startPos.x * 4 + 20, startPos.y));
}//end game stats

void gamestats::setstring(std::string str, int data, stats kind)
{
	switch (kind)
	{
	case Time:
		if(data != -1)//if level is unlimited - don't print the time (int) data
			str.append(std::to_string(data));//attach int data to the string
		m_time.setText(str);
		break;
	case level:
		str.append(std::to_string(data));//attach int data to the string
		m_level.setText(str);
		break;
	case score:
		str.append(std::to_string(data));//attach int data to the string
		m_score.setText(str);
		break;
	case life:
		str.append(std::to_string(data));//attach int data to the string
		m_life.setText(str);
		break;
	}
}//end setstring

void gamestats::changeColor(const sf::Color& color, stats kind)
{
	switch (kind)
	{
	case Time:
		m_time.setColor(color);
		break;
	case level:
		m_level.setColor(color);
		break;
	case score:
		m_score.setColor(color);
		break;
	case life:
		m_life.setColor(color);
		break;
	}
}//end changeColor

void gamestats::draw(sf::RenderWindow& window) const
{
	m_time.draw(window);
	m_level.draw(window);
	m_score.draw(window);
	m_life.draw(window);
}//end draw



