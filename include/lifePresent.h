#pragma once
#include <SFML/Graphics.hpp>
#include "present.h"

class lifePresent : public present {
public:
	using present::present;
	virtual void handleCollision(player& player, bool WhileFalling = false) override;
	virtual void handleCollision(enemy& enemy, bool WhileFalling = false) override;
private:

};