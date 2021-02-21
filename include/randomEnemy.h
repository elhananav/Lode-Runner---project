#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "macros.h"
#include "ladder.h"
#include "pole.h"
#include "player.h"

class randomEnemy : public enemy {
public:
	randomEnemy(const sf::Sprite& sprite);
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
	sf::Clock m_clock;//for direction change
};