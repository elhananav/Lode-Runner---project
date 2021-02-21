#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class player;
class wall;
class ladder;
class enemy;
class pole;
class Present;
class coin;

//abstract class - basic class for all objects in the game
class gameObject {
public:
	gameObject(const sf::Sprite& sprite);
	virtual void draw(sf::RenderWindow& window) = 0;
	const sf::Vector2f& getPosition() const;
	sf::Vector2f getSize() const;
	const sf::Sprite& getSprite() const;
	void setPosition(const sf::Vector2f& location);
	void setSize(const sf::Vector2f& size);
	bool collidesWith(const gameObject& obj) const;
	virtual void handleCollision(gameObject& obj, bool WhileFalling = false) = 0;
	virtual void handleCollision(player& player, bool WhileFalling = false) = 0;
	virtual void handleCollision(wall& wall, bool WhileFalling = false) = 0;
	virtual void handleCollision(enemy& enemy, bool WhileFalling = false) = 0;
	virtual void handleCollision(ladder& ladder, bool WhileFalling = false) = 0;
	virtual void handleCollision(pole& pole, bool WhileFalling = false) = 0;
	virtual void handleCollision(Present& Present, bool WhileFalling = false) = 0;
	virtual void handleCollision(coin& coin, bool WhileFalling = false) = 0;

private:
	sf::Sprite m_sprite;
};