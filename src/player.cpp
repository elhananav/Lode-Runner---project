#include "player.h"
#include "board.h"



player::player(const sf::Sprite& sprite, int score, int life, int numlevel)
	:moveable(sprite), m_life(life), m_score(score), m_numOfLevel(numlevel),
	m_IAmDead(false), m_time(0), m_presentKind(nothing)
{
}//end constructor

void player::move(const sf::Time& time)
{
	setPDirection();
	float speed = PLAYER_SPEED * time.asSeconds();
	setLastLocation(getPosition());
	if (canMove(speed, getDirection()))
	{
		auto location = sf::Vector2f(getPosition().x + speed * getDirection().x,
			getPosition().y + speed * getDirection().y);
		setPosition(location);
	}
}//end move

void player::setPDirection()
{//set direction according to user press
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		setDirection(sf::Vector2f(-1, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		setDirection(sf::Vector2f(1, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		setDirection(sf::Vector2f(0, -1));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		setDirection(sf::Vector2f(0, 1));
	}
	else
		setDirection(sf::Vector2f(0, 0));
}//end setPDirection

void player::excavate(excavateSide side, const board& board)
{//excavate a hole in the board
	sf::Vector2i slotsIndex[2];

	auto location = getPosition();
	location.y += 5.0f;//to get the one underneath 

	board.getSlotslotsIndex(location, sf::Vector2f(0, 1)/*down*/, slotsIndex);

	sf::Vector2i index;
	if (slotsIndex[0] == slotsIndex[1])//means we are exactly on one place
		(side == left) ? index = sf::Vector2i(slotsIndex[0].x, slotsIndex[0].y - 1) : index = sf::Vector2i(slotsIndex[0].x, slotsIndex[0].y + 1);
	else
	{
		if (side == left)//left down vertex
			index = slotsIndex[0];
		else if (side == right)
			index = slotsIndex[1];//right down vertex
	}

	//so it wont excavate under a ladder
	if (board.slotsOutOfBounds(index) ||
		(board.getStaticObj(sf::Vector2i(index.x - 1, index.y)) && board.getStaticObj(sf::Vector2i(index.x - 1, index.y))->getExistens()))
		return;
	//so it wouldn't try to excavate empty place/pole/ladder
	if (!board.getStaticObj(index) || typeid(*board.getStaticObj(index)) != typeid(wall))
		return;
	auto Wall = dynamic_cast<wall*>(board.getStaticObj(index));
	Wall->setExistens(false);
	Wall->startClock();

	m_excavatedWallIndex.push_back(index);
}//end excavate

void player::addScore(int score)
{
	m_score += score;
}//end addScore

void player::addTime(int time)
{
	m_time += time;
}//end addTime

void player::addLife(int num)
{
	m_life += num;
}//end addLife

void player::reduceLife()
{
	--m_life;
}//end reduceLife

const sf::Vector2i& player::getExcavatedWallIndex(int place) const
{
	return m_excavatedWallIndex[place];
}//end getExcavatedWallIndex

int player::getNumOfexcavateed() const
{//return how many walls are excavated
	return m_excavatedWallIndex.size();
}//end getNumOfexcavateed

int player::getLife() const
{
	return m_life;
}//end getLife

int player::getScore() const
{
	return m_score;
}//end getScore

bool player::getIAmDead() const
{
	return m_IAmDead;
}//end getIAmDead

PresentType player::getPresentKind() const
{
	return m_presentKind;
}//end getPresentKind

void player::setPresentKind(PresentType type)
{
	m_presentKind = type;
}//end setPresentKind

void player::setNumOfLevel(int num)
{
	m_numOfLevel = num;
}//end setNumOfLevel

void player::handleCollision(gameObject& obj, bool WhileFalling)
{
	obj.handleCollision(*this, WhileFalling);
}//end handleCollision with gameObject

void player::handleCollision(player& player, bool WhileFalling)
{
	//has no meaning
}//end handleCollision with player

void player::handleCollision(ladder& ladder, bool WhileFalling)
{
	//if the player fell on a ladder
	if (WhileFalling)
	{
		//then cant go up(because he is on the top of the ladder)
		setPosition(getLastLocation());
		setUpPossibale(false);
	}
	else
		setUpPossibale(true);
	//if move up\down while on a ladder - set player location(only col) as the ladder location
	if (getDirection() == sf::Vector2f(0, -1) || getDirection() == sf::Vector2f(0, 1))
		setPosition(sf::Vector2f(ladder.getPosition().x, getPosition().y));

	setNeedToFall(false);
}//end handleCollision with enemy

void player::handleCollision(wall& wall, bool WhileFalling)
{
	if (WhileFalling)
	{
		setUpPossibale(false);
	}
	setPosition(getLastLocation());
}//end handleCollision with wall

void player::handleCollision(enemy& enemy, bool WhileFalling)
{
	m_IAmDead = true;
	--m_life;
}//end handleCollision with enemy

void player::handleCollision(pole& pole, bool WhileFalling)
{
	setNeedToFall(false);
	auto location = pole.getPosition();
	location.x = getPosition().x;
	location.y += 0.5f;//so it will be possible to drop down with one press
	setPosition(location);
}//end handleCollision with pole

void player::handleCollision(Present& Present, bool WhileFalling)
{
	//handled at specific preset handleCollision
}//end handleCollision with Present

void player::handleCollision(coin& coin, bool WhileFalling)
{
	setNeedToFall(true);
	if (coin.getExistens())
	{
		m_score += m_numOfLevel * COINVALUE;
	}
}//end handleCollision with coin
