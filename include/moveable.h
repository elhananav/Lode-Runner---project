#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "gameObject.h"
#include "macros.h"

class board;
class staticObj;
class player;
class wall;

//abstract class
class moveable : public gameObject{
public:
	moveable(const sf::Sprite& sprite);
	virtual void move(const sf::Time& time) = 0;
	void moveFalldown(const board& baord, const sf::Time& time, int index);
	virtual void draw(sf::RenderWindow& window) override;
	bool canMove(float speed, const sf::Vector2f& direction) const;
	const sf::Vector2f& getDirection() const;
	const sf::Vector2f& getLastLocation() const;
	bool getIsUpPossibale() const;
	bool getInAHole() const;
	bool getNeedToFall() const;
	void setDirection(const sf::Vector2f& direction);
	void setLastLocation(const sf::Vector2f& location);
	void setUpPossibale(bool booloiany);
	void setInAHole(bool booloiany);
	void setNeedToFall(bool booloiany);
	
private:
	bool fallIntoAHole(const board& baord, int index, sf::Vector2i slotsIndex[2]);
	sf::Vector2f m_direction;
	sf::Vector2f m_lastLocation;
	bool m_isUpPossibale;
	bool m_inAHole;
	bool m_needToFall;
};