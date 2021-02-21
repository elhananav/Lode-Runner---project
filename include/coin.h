#pragma once
#include <SFML/Graphics.hpp>
#include "staticObj.h"
#include "player.h"

class coin : public staticObj {
public:
	coin(const sf::Sprite& sprite);
	virtual void handleCollision(player& player, bool WhileFalling = false) override;
	virtual void handleCollision(enemy& enemy, bool WhileFalling = false) override;
	static int getCoinCounter();
	static void setCoinCounter(int count);

private:
	static int m_coinCounter;//count how many Existing coins there is
};