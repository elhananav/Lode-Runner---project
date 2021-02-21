#include "constEnemy.h"

constEnemy::constEnemy(const sf::Sprite& sprite, const board& board)
	:enemy(sprite), m_board(board)
{
	//set first direction to be right
	setDirection(sf::Vector2f(1, 0));
}//end constEnemy constructor

void constEnemy::move(const sf::Time& time)
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
	else
		setDirection(sf::Vector2f(getDirection().x * -1, 0));//Reverse the direction
}//end move

void constEnemy::setEDirection()
{
	sf::Vector2i slotsIndex[2];
	auto location = getPosition();

	location.y += 5.0f;//do get diagonal down slot
	m_board.getSlotslotsIndex(location, getDirection(), slotsIndex);

	//so will not be exception from static vector
	if (m_board.slotsOutOfBounds(slotsIndex[0]) || m_board.slotsOutOfBounds(slotsIndex[1]))
		setDirection(sf::Vector2f(getDirection().x * -1, 0));//Reverse the direction

	//diagonal down slot
	else if (!m_board.getStaticObj(slotsIndex[1]))
		setDirection(sf::Vector2f(getDirection().x * -1, 0));//Reverse the direction
}//end setEDirection

void constEnemy::handleCollision(gameObject& obj, bool WhileFalling)
{
	obj.handleCollision(*this, WhileFalling);
}//end handleCollision with gameObject

void constEnemy::handleCollision(player& player, bool WhileFalling)
{
	player.handleCollision(*this, WhileFalling);
}//end handleCollision with player

void constEnemy::handleCollision(wall& wall, bool WhileFalling)
{
	setPosition(getLastLocation());
}//end handleCollision with wall

void constEnemy::handleCollision(enemy& enemy, bool WhileFalling)
{
	//has no meaning
}//end handleCollision with enemy

void constEnemy::handleCollision(ladder& ladder, bool WhileFalling)
{
	setNeedToFall(false);
	//if the constEnemy fell on a ladder
	if (WhileFalling)
	{
		//then cant go up(because he is on the top of the ladder)
		setPosition(getLastLocation());
		setUpPossibale(false);
	}
	else
		setUpPossibale(true);
}//end handleCollision with ladder

void constEnemy::handleCollision(pole& pole, bool WhileFalling)
{
	setNeedToFall(false);
	setDirection(sf::Vector2f(getDirection().x * -1, 0));//Reverse the direction
}//end handleCollision with pole

void constEnemy::handleCollision(Present& Present, bool WhileFalling)
{
	setNeedToFall(true);
}//end handleCollision with Present

void constEnemy::handleCollision(coin& coin, bool WhileFalling)
{
	setNeedToFall(true);
}//end handleCollision with coin
