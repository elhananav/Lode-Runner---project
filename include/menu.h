#pragma once
#include <SFML/Graphics.hpp>
#include "textures.h"
#include "macros.h"
#include "text.h"

const sf::Vector2f BACKGROUNDSIZE(1200, 800);
const sf::Vector2f BUTTON_SIZE(200, 100);
enum Button {Play, Exit, Nothing};
enum overMenu { GameOver, Level, Score };

class menu {
public:
	menu(const textures& textures, const sf::Font& font);
	void handleMouse(const sf::Vector2f& location);
	void draw(sf::RenderWindow& window) const;//draw the open screen
	void drawFinal(sf::RenderWindow& window) const;//draw the final(game over) screen
	Button whoIsPressed(const sf::Vector2f& location);
	void setstring(std::string str, overMenu kind, int data = 0);

private:
	sf::Sprite m_play;
	sf::Sprite m_exit;
	sf::Sprite m_background;
	sf::Sprite m_backgroundGameOver;
	text m_gameOver;//if the player won or strike before
	text m_level;
	text m_score;
};