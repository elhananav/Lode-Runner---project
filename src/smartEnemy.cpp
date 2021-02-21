#include "smartEnemy.h"
#include "board.h"

smartEnemy::smartEnemy(const sf::Sprite& sprite, player* player)
	: enemy(sprite), m_player(player)
{
	setDirection(sf::Vector2f(1, 0));
}//end constructor

void smartEnemy::move(const sf::Time& time)
{
	//if enemy is on a ladder - than handle setDirection at handleCollision(with ladder)
	if(!getIsUpPossibale())
		setEDirection();
	float speed = ENEMY_SPEED * time.asSeconds();
	setLastLocation(getPosition());
	if (canMove(speed, getDirection()))
	{
		auto location = sf::Vector2f(getPosition().x + speed * getDirection().x,
			getPosition().y + speed * getDirection().y);
		setPosition(location);
	}
	else
		setDirection(sf::Vector2f(getDirection().x * -1, 0));//Reverse the direction
}//end move

void smartEnemy::setEDirection()
{
	if (getPosition().x > m_player->getPosition().x)
		setDirection(sf::Vector2f(-1, 0));//left
	if (getPosition().x < m_player->getPosition().x)
		setDirection(sf::Vector2f(1, 0));//right
}//end setEDirection

void smartEnemy::handleCollision(gameObject& obj, bool WhileFalling)
{
	obj.handleCollision(*this, WhileFalling);
}//end handleCollision with gameObject

void smartEnemy::handleCollision(player& player, bool WhileFalling)
{
	player.handleCollision(*this, WhileFalling);
}//end handleCollision with player

void smartEnemy::handleCollision(wall& wall, bool WhileFalling)
{
	if (WhileFalling)
	{
		setUpPossibale(false);
	}
	setPosition(getLastLocation());
	setDirection(sf::Vector2f(getDirection().x * -1, 0));//Reverse the direction
}//end handleCollision with enemy

void smartEnemy::handleCollision(enemy& enemy, bool WhileFalling)
{
	//has no meaning
}//end handleCollision with enemy

void smartEnemy::handleCollision(ladder& ladder, bool WhileFalling)
{
	if (WhileFalling)
	{
		setPosition(getLastLocation());
		setUpPossibale(false);
	}
	else
	{
		setUpPossibale(true);
		if (getPosition().y - m_player->getPosition().y > 2.0f)//if player above enemy
		{
			setDirection(sf::Vector2f(0, -1));//up
		}
	}
	//if move up\down while on a ladder - set enemy location(only col) as the ladder location
	if (getDirection() == sf::Vector2f(0, -1) || getDirection() == sf::Vector2f(0, 1))
		setPosition(sf::Vector2f(ladder.getPosition().x, getPosition().y));

	setNeedToFall(false);
}//end handleCollision with ladder

void smartEnemy::handleCollision(pole& pole, bool WhileFalling)
{
	setNeedToFall(false);
	auto location = pole.getPosition();
	location.x = getPosition().x;
	location.y += 0.5f;//so it will be possible to drop down
	setPosition(location);
}//end handleCollision with pole

void smartEnemy::handleCollision(Present& Present, bool WhileFalling)
{
	setNeedToFall(true);
}//end handleCollision with Present

void smartEnemy::handleCollision(coin& coin, bool WhileFalling)
{
	setNeedToFall(true);
}//end handleCollision with coin


