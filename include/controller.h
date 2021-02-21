#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"
#include <vector>
#include "textures.h"
#include "menu.h"
#include "gamestats.h"
#include "coin.h"
#include "macros.h"

const char NAME_FILE[] = "board.txt";
enum gameStatus { Failed, Finish };

class controller {
public:
	controller();
	void run();
	void runMenu();

private:
	bool isLevelFinish() const;
	void setGameStats();
	void gameOver(gameStatus status);
	void setGameOverStats(gameStatus status);
	void checkLevelFinish();
	void waitUntilKeyPress();
	bool isAnyKeyPressed() const;
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	sf::Sound m_backgroundSound;
	sf::Sprite m_background;
	board m_board;
	textures& m_textures;
	menu m_menu;
	gamestats m_gamestats;
	int m_numOfLevel;
};