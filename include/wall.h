#pragma once
#include <SFML/Graphics.hpp>
#include "staticObj.h"
#include "player.h"
#include "enemy.h"
#include "macros.h"

class wall : public staticObj {
public:
	wall(const sf::Sprite& sprite);
	void startClock();
	sf::Time getTime() const;
	bool getIsFull() const;
	int getMovableIndex() const;
	void setIsFull(bool isFull);
	void setMovableIndex(int index);
	virtual void handleCollision(player& player, bool WhileFalling = false) override;
	virtual void handleCollision(enemy& enemy, bool WhileFalling = false) override;

private:
	sf::Clock m_clock;
	bool m_isFull;
	int m_movableIndex;//save movable index in vector(which movable is in this obj)
};