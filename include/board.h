#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "moveable.h"
#include "staticObj.h"
#include "macros.h"
#include "player.h"
#include "coin.h"
#include "wall.h"
#include "ladder.h"
#include "pole.h"
#include "enemy.h"
#include "text.h"
#include "randomEnemy.h"
#include "smartEnemy.h"
#include "constEnemy.h"
#include <fstream>
#include "textures.h"
#include "badPresent.h"
#include "lifePresent.h"
#include "scorePresent.h"
#include "timePresent.h"
#include "levelObj.h"

const int PLAYER_PLACE = 0;

class controller;

class board {
public:
	board();
	bool loadLevel(int numOfLevel);
	void move(const sf::Time& time);
	void levelEnded(int numOfLevel);
	void restartLevel(int numOfLevel);
	void resetGameData();
	void updateTime();
	void pushUpMsg(sf::Clock& clockPresent, sf::RenderWindow& window);
	void excavate(excavateSide side);
	void bringBackExcavated();
	bool slotsOutOfBounds(sf::Vector2i index) const;
	void handlePresent(sf::Clock& clockPresent);
	bool needToHandleCollision(const sf::Vector2i& index, int i) const;
	void draw(sf::RenderWindow& window);
	int getScore() const;
	int getLife() const;
	int getLevelTime() const;
	bool getIsPlayerDead() const;
	const levelObj& getlevel() const;
	void getSlotslotsIndex(const sf::Vector2f& location, const sf::Vector2f& direction, sf::Vector2i* index) const;
	staticObj* getStaticObj(const sf::Vector2i& index) const;

private:
			/*private function*/
	void addEnemytoGame();//add enemy when player 'eat' enemy present
	bool needToCheckFalldown(const sf::Vector2i index[], int i);
	void clearVectors();
	sf::Sprite createSprite(simbolIndex type, int col, int row);
	std::unique_ptr<staticObj> createPresent(int col, int row);
	std::unique_ptr<moveable> createEnemy(int col, int row);

			/*private members*/
	std::vector <std::unique_ptr<moveable>> m_moveable;
	std::vector <std::vector<std::unique_ptr<staticObj>>> m_static;
	std::vector<sf::Vector2i> m_excavatedWallIndex;
	sf::Vector2f m_size;//size of each square(in pixels)
	sf::Clock m_clock;
	int m_levelCurrentTime;
	levelObj m_level;
	text m_pushUpMsg;
	bool m_tookPresent;
	PresentType m_presentType;
};

