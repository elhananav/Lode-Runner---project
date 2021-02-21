#pragma once
#include <SFML/Graphics.hpp>
#include "text.h"

enum stats{Time, level, score, life};

class gamestats
{
public:
	gamestats(const sf::Font& font);
	void setstring(std::string str, int data, stats kind);
	void changeColor(const sf::Color& color, stats kind);
	void draw(sf::RenderWindow& window) const;
private:
	text m_time;
	text m_level;
	text m_score;
	text m_life;
};
	
