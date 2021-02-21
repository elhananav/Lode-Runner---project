#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "moveable.h"
#include "staticObj.h"
#include "wall.h"
#include "coin.h"
#include "ladder.h"
#include "pole.h"
#include "music.h"
#include "macros.h"

const int COINVALUE = 2;
const int LEVELFINISH = 50;

enum PresentType{addTime, addEnemy, addScore, addLife, nothing};

class player : public moveable {
public:
	player(const sf::Sprite& sprite, int score, int life, int numlevel);
	virtual void move(const sf::Time& time) override;
	void excavate(excavateSide side, const board& board);
	void reduceLife();
	void addScore(int score);
	void addTime(int time);
	void addLife(int num);
	const sf::Vector2i& getExcavatedWallIndex(int place) const;
	int getNumOfexcavateed() const;
	int getLife() const;
	int getScore() const;
	bool getIAmDead() const;
	PresentType getPresentKind() const;
	void setPresentKind(PresentType type);
	void setNumOfLevel(int num);
	virtual void handleCollision(gameObject& obj, bool WhileFalling = false) override;
	virtual void handleCollision(player& player, bool WhileFalling = false) override;
	virtual void handleCollision(ladder& ladder, bool WhileFalling = false) override;
	virtual void handleCollision(wall& wall, bool WhileFalling = false) override;
	virtual void handleCollision(enemy& enemy, bool WhileFalling = false) override;
	virtual void handleCollision(pole& pole, bool WhileFalling = false) override;
	virtual void handleCollision(Present& Present, bool WhileFalling = false) override;
	virtual void handleCollision(coin& coin, bool WhileFalling = false) override;

private:
	void setPDirection();

	bool m_IAmDead;
	int m_numOfLevel;
	int m_life;
	int m_score;
	int m_time;
	PresentType m_presentKind;
	std::vector<sf::Vector2i> m_excavatedWallIndex;//save all excavated Walls static vector indexes
};