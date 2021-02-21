#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "board.h"
#include "macros.h"

class pole;

class constEnemy : public enemy {
public:
	constEnemy(const sf::Sprite& sprite, const board& board);
	virtual void move(const sf::Time& time) override;
	virtual void setEDirection() override;
	virtual void handleCollision(gameObject& obj, bool WhileFalling = false) override;
	virtual void handleCollision(player& player, bool WhileFalling = false) override;
	virtual void handleCollision(wall& wall, bool WhileFalling = false) override;
	virtual void handleCollision(enemy& enemy, bool WhileFalling = false) override;
	virtual void handleCollision(ladder& ladder, bool WhileFalling = false) override;
	virtual void handleCollision(pole& pole, bool WhileFalling = false) override;
	virtual void handleCollision(Present& Present, bool WhileFalling = false) override;
	virtual void handleCollision(coin& coin, bool WhileFalling = false) override;

private:
	const board& m_board;//for the movement
};