#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "macros.h"

class player;

class smartEnemy : public enemy {
public:
	smartEnemy(const sf::Sprite& sprite, player* player);
	virtual void move(const sf::Time& time) override;
	virtual void handleCollision(gameObject& obj, bool WhileFalling = false) override;
	virtual void handleCollision(player& player, bool WhileFalling = false) override;
	virtual void handleCollision(wall& wall, bool WhileFalling = false) override;
	virtual void handleCollision(enemy& enemy, bool WhileFalling = false) override;
	virtual void handleCollision(ladder& ladder, bool WhileFalling = false) override;
	virtual void handleCollision(pole& pole, bool WhileFalling = false) override;
	virtual void handleCollision(Present& Present, bool WhileFalling = false) override;
	virtual void handleCollision(coin& coin, bool WhileFalling = false) override;

private:
	virtual void setEDirection() override;
	player* m_player;//so smartEnemy could chase player
};