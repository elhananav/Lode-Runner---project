#include "moveable.h"
#include "board.h"


moveable::moveable(const sf::Sprite& sprite)
	: gameObject(sprite), m_direction(sf::Vector2f(0, 0)/*no direction*/), m_isUpPossibale(false),
		m_inAHole(false), m_needToFall(false)
{
}//end constructor

void moveable::draw(sf::RenderWindow& window)
{
	window.draw(getSprite());
}//end draw

void moveable::moveFalldown(const board& Board, const sf::Time& time, int index)
{
	sf::Vector2i slotsIndex[2];
	//speed is faster when falling
	float speed = 800 * time.asSeconds();
	setLastLocation(getPosition());

	if (canMove(speed, sf::Vector2f(0, 1)))
	{
		auto location = sf::Vector2f(getPosition().x, getPosition().y + speed * 1);
		setPosition(location);
		Board.getSlotslotsIndex(location, sf::Vector2f(0, 1), slotsIndex);

		//collides with one place
		if (slotsIndex[0] == slotsIndex[1] && Board.getStaticObj(slotsIndex[0]))
		{
			//check if need to fall to an excavated wall
			if (!fallIntoAHole(Board, index, slotsIndex))
				handleCollision(*Board.getStaticObj(slotsIndex[0]), true);
		}
		//collides with two places
		else
		{
			//if collision occurred with at least one cell that isn't empty
			if (Board.needToHandleCollision(slotsIndex[0], index))
				handleCollision(*Board.getStaticObj(slotsIndex[0]), true);

			if (Board.needToHandleCollision(slotsIndex[1], index))
				handleCollision(*Board.getStaticObj(slotsIndex[1]), true);
		}
	}
}//end moveFalldown

bool moveable::canMove(float speed, const sf::Vector2f& direction) const
{//return if the object try to move outside from the window
	if (direction == sf::Vector2f(0, -1) && !m_isUpPossibale)//preventing from moving up without a ladder
		return false;
	if (getPosition().x + getSize().x + direction.x * speed > (float)BOARDSIZE_X)
		return false;

	if (getPosition().x + direction.x * speed < 0)
		return false;

	if (getPosition().y + getSize().y + direction.y * speed > (float)BOARDSIZE_Y)
		return false;

	if (getPosition().y + direction.y * speed < 0)
		return false;
	return true;
}//end canMove

bool moveable::fallIntoAHole(const board& baord, int index, sf::Vector2i slotsIndex[2])
{
	//check if need to fall to an excavated wall
	if (typeid(*baord.getStaticObj(slotsIndex[0])) == typeid(wall) && !baord.getStaticObj(slotsIndex[0])->getExistens())
	{
		auto Wall = dynamic_cast<wall*>(baord.getStaticObj(slotsIndex[0]));
		//only if the place isn't occupied with other moving object
		if (!Wall->getIsFull())
		{
			//change location into to the hole
			setPosition(baord.getStaticObj(slotsIndex[0])->getPosition());
			Wall->setIsFull(true);
			Wall->setMovableIndex(index);
			m_inAHole = true;
		}
		else
			handleCollision(*baord.getStaticObj(slotsIndex[0]), true);
		return true;
	}
	return false;
}//end fallIntoAHole

const sf::Vector2f& moveable::getDirection() const
{
	return m_direction;
}//end getDirection

const sf::Vector2f& moveable::getLastLocation() const
{
	return m_lastLocation;
}//end getLastLocation

bool moveable::getIsUpPossibale() const
{
	return m_isUpPossibale;
}//end setUpPossibale

bool moveable::getInAHole() const
{
	return m_inAHole;
}//end setUpPossibale

bool moveable::getNeedToFall() const
{
	return m_needToFall;
}//end setUpPossibale

void moveable::setUpPossibale(bool booloiany)
{
	m_isUpPossibale = booloiany;
}//end setUpPossibale

void moveable::setLastLocation(const sf::Vector2f& location)
{
	m_lastLocation = location;
}//end setLastLocation

void moveable::setDirection(const sf::Vector2f& direction)
{
	m_direction = direction;
}//end setDirection

void moveable::setInAHole(bool booloiany)
{
	m_inAHole = booloiany;
}//end setUpPossibale

void moveable::setNeedToFall(bool booloiany)
{
	m_needToFall = booloiany;
}//end setUpPossibale







