#include "coin.h"

int coin::m_coinCounter = 0;

coin::coin(const sf::Sprite& sprite): staticObj(sprite)
{//coin constructor - count how many coins where crated 
	++m_coinCounter;
}//end coin constructor

void coin::handleCollision(player& player, bool WhileFalling)
{
	if (getExistens())
	{
		--m_coinCounter;
	}
	player.handleCollision(*this, WhileFalling);
	setExistens(false);
}//end handleCollision with player

void coin::handleCollision(enemy& enemy, bool WhileFalling)
{
	enemy.handleCollision(*this);
}//end handleCollision with enemy


int coin::getCoinCounter()
{//static func - return the number of existing coins
	return m_coinCounter;
}//end getCoinCounter

void coin::setCoinCounter(int count)
{//static func
	m_coinCounter = count;
}//end setCoinCounter
