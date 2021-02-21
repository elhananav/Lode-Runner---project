#include "menu.h"

const sf::Vector2f gameoverPlace(280, 250); //the place to print the game-over menu text

menu::menu(const textures& textures, const sf::Font& font)
	: m_background(), m_backgroundGameOver(), m_play(), m_exit(),
	m_level(font), m_score(font), m_gameOver(font)
{

	m_background.setTexture(textures.getTexture(MENU_BACKGROUND));
	m_background.setScale((BACKGROUNDSIZE.x / m_background.getLocalBounds().width),
		(BACKGROUNDSIZE.y / m_background.getLocalBounds().height));
	m_background.setPosition(sf::Vector2f(0, 0));

	m_backgroundGameOver.setTexture(textures.getTexture(GAMEOVER_BACKGROUND));
	m_backgroundGameOver.setScale((BACKGROUNDSIZE.x / m_backgroundGameOver.getLocalBounds().width),
		(BACKGROUNDSIZE.y / m_backgroundGameOver.getLocalBounds().height));
	m_backgroundGameOver.setPosition(sf::Vector2f(0, 0));

	m_play.setTexture(textures.getTexture(PLAY_BUTTON));
	m_play.setScale((BUTTON_SIZE.x / m_play.getLocalBounds().width),
		(BUTTON_SIZE.y / m_play.getLocalBounds().height));
	m_play.setPosition(BACKGROUNDSIZE.x / 2 - (BUTTON_SIZE.x / 2), (BACKGROUNDSIZE.y / 2) + 100.0f);

	m_exit.setTexture(textures.getTexture(EXIT_BUTTON));
	m_exit.setScale((BUTTON_SIZE.x / m_exit.getLocalBounds().width),
		(BUTTON_SIZE.y / m_exit.getLocalBounds().height));
	m_exit.setPosition(BACKGROUNDSIZE.x / 2 - (BUTTON_SIZE.x / 2), (BACKGROUNDSIZE.y / 2 + 100.0f) + BUTTON_SIZE.y + 50);
	//text  positions-  game-over menu
	m_gameOver.setPosition(sf::Vector2f(gameoverPlace.x, gameoverPlace.y));
	m_score.setPosition(sf::Vector2f(gameoverPlace.x, gameoverPlace.y + 50));
	m_level.setPosition(sf::Vector2f(gameoverPlace.x, gameoverPlace.y + 100));
}//end menu constructor


void menu::handleMouse(const sf::Vector2f& location)
{
	if (m_play.getGlobalBounds().contains(location))
		m_play.setColor(sf::Color::Yellow);
	else if (m_exit.getGlobalBounds().contains(location))
		m_exit.setColor(sf::Color::Yellow);
	else
	{
		m_play.setColor(sf::Color::White);
		m_exit.setColor(sf::Color::White);
	}
}//end handleMouse

void menu::draw(sf::RenderWindow& window) const
{
	window.draw(m_background);
	window.draw(m_play);
	window.draw(m_exit);
}//end draw

void menu::drawFinal(sf::RenderWindow& window) const
{
	window.draw(m_backgroundGameOver);
	m_gameOver.draw(window);
	m_level.draw(window);
	m_score.draw(window);
	window.draw(m_play);
	window.draw(m_exit);
}//end drawFinal

Button menu::whoIsPressed(const sf::Vector2f& location)
{
	if (m_play.getGlobalBounds().contains(location))
		return Play;
	else if (m_exit.getGlobalBounds().contains(location))
		return Exit;
	else
		return Nothing;
}//end whoIsPressed

void menu::setstring(std::string str, overMenu kind, int data)
{
	switch (kind)
	{
	case GameOver:
		m_gameOver.setText(str);
		break;
	case Level:
		str.append(std::to_string(data));
		m_level.setText(str);
		break;
	case Score:
		str.append(std::to_string(data));
		m_score.setText(str);
		break;
	}
}//end setstring

