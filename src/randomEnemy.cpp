#include "randomEnemy.h"

randomEnemy::randomEnemy(const sf::Sprite& sprite) : enemy(sprite)
{
	m_clock.restart();
}//end constructor

void randomEnemy::move(const sf::Time& time)
{
	setEDirection();
	float speed = ENEMY_SPEED * time.asSeconds();
	setLastLocation(getPosition());
	if (canMove(speed, getDirection()))
	{
		auto location = sf::Vector2f(getPosition().x + speed * getDirection().x,
									 getPosition().y + speed * getDirection().y);
		setPosition(location);
	}
}//end move

void randomEnemy::setEDirection()
{
	int side;
	if (m_clock.getElapsedTime().asSeconds() > 2)
	{
		m_clock.restart();
		side = rand() % 2;
	}
	else
		side = 2;

	switch (side)
	{
	case 0://right
		setDirection(sf::Vector2f(1, 0));
		break;
	case 1://left
		setDirection(sf::Vector2f(-1, 0));
		break;
	case 2://do not change direction
		break;
	}
}//end setEDirection

void randomEnemy::handleCollision(gameObject& obj, bool WhileFalling)
{
	obj.handleCollision(*this, WhileFalling);
}//end handleCollision with gameObject

void randomEnemy::handleCollision(player& player, bool WhileFalling)
{
	player.handleCollision(*this, WhileFalling);
}//end handleCollision with player

void randomEnemy::handleCollision(wall& wall, bool WhileFalling)
{
	if (WhileFalling)
	{
		setUpPossibale(false);
	}
	setPosition(getLastLocation());
}//end handleCollision with wall

void randomEnemy::handleCollision(enemy& enemy, bool WhileFalling)
{
	//has no meaning
}//end handleCollision with enemy

void randomEnemy::handleCollision(ladder& ladder, bool WhileFalling)
{
	setNeedToFall(false);
	//if the randomEnemy fell on a ladder
	if (WhileFalling)
	{
		//then cant go up(because he is on the top of the ladder)
		setPosition(getLastLocation());
		setUpPossibale(false);
	}
	else
	{
		setUpPossibale(true);
		int side = rand() % 100;//if collides with ladder - sometimes go up, sometimes not
		if (side == 0)
			setDirection(sf::Vector2f(0, -1));//up

		if (getDirection() == sf::Vector2f(0, -1)/*up*/ || getDirection() == sf::Vector2f(0, 1)/*down*/)
			setPosition(sf::Vector2f(ladder.getPosition().x, getPosition().y));
	}
}//end handleCollision with ladder

void randomEnemy::handleCollision(pole& pole, bool WhileFalling)
{
	setNeedToFall(false);
	auto location = pole.getPosition();
	location.x = getPosition().x;
	location.y += 0.5f;//so it will be possible to drop down with one press
	setPosition(location);
}//end handleCollision with pole

void randomEnemy::handleCollision(Present& Present, bool WhileFalling)
{
	setNeedToFall(true);
}//end handleCollision with Present

void randomEnemy::handleCollision(coin& coin, bool WhileFalling)
{
	setNeedToFall(true);
}//end handleCollision with coin


