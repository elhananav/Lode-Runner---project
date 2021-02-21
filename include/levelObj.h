#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "textures.h"

class levelObj {
public:
	levelObj();
	bool loadLevel(int numOfLevel);
	int getScore() const;
	int getLife() const;
	int getNumOfCoin() const;
	int getLevelTime() const;
	void setScore(int score);
	void setLife(int life);
	void clear();
	const sf::Vector2i& getNumOfSquares() const;
	char operator()(int, int) const;

private:
	std::ifstream m_file;
	std::vector<std::vector<char>> m_level;
	sf::Vector2i m_numOfSquares;//store the num of squares(x,y), getting from file when load level
	int m_score;
	int m_life;
	int m_levelTime;
	int m_numOfCoins;//store the num of coins in level(at start)
};