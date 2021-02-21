#include "staticObj.h"

staticObj::staticObj(const sf::Sprite& sprite)
	:gameObject(sprite),m_exists(true)
{
}//end constructor

void staticObj::draw(sf::RenderWindow& window)
{
	if (m_exists)
		window.draw(getSprite());
}//end draw

bool staticObj::getExistens() const
{
	return m_exists;
}//end getExistens

void staticObj::setExistens(bool booliany)
{
	m_exists = booliany;
}//end setExistens

//static collides with other static has no meaning - so all static handleCollision is here, instead in each static obj
void staticObj::handleCollision(gameObject& obj, bool WhileFalling) {}

void staticObj::handleCollision(enemy& enemy, bool WhileFalling) {}

void staticObj::handleCollision(wall& wall, bool WhileFalling) {}

void staticObj::handleCollision(ladder& ladder, bool WhileFalling) {}

void staticObj::handleCollision(pole& pole, bool WhileFalling) {}

void staticObj::handleCollision(Present& Present, bool WhileFalling) {}

void staticObj::handleCollision(coin& coin, bool WhileFalling) {}


