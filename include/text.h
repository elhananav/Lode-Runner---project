#pragma once
#include <SFML/Graphics.hpp>


class text {
public:
	text(const sf::Font& font);
	void draw(sf::RenderWindow& window) const;
	void setColor(const sf::Color& color);
	void setText(std::string str);
	void setPosition(const sf::Vector2f& location);
	void setCharacterSize(int size);

private:
	sf::Text m_text;
};