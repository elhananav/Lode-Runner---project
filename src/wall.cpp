#include "wall.h"

wall::wall(const sf::Sprite& sprite):staticObj(sprite), m_isFull(false), m_movableIndex(-1)
{
}//end constructor

void wall::startClock()
{
	m_clock.restart();
}//end startClock

sf::Time wall::getTime() const
{
	return m_clock.getElapsedTime();
}//end getTime

bool wall::getIsFull() const
{
	return m_isFull;
}//end getIsFull

int wall::getMovableIndex() const
{
	return m_movableIndex;
}//end getMovableIndex

void wall::setIsFull(bool isFull)
{
	m_isFull = isFull;
}//end setIsFull

void wall::setMovableIndex(int index)
{
	m_movableIndex = index;
}//end setMovableIndex

void wall::handleCollision(player& player, bool WhileFalling)
{
	player.handleCollision(*this, WhileFalling);
}//end handleCollision with player

void wall::handleCollision(enemy& enemy, bool WhileFalling)
{
	enemy.handleCollision(*this, WhileFalling);
}//end handleCollision with enemy

