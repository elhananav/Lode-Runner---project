#pragma once
#include <SFML/Graphics.hpp>
#include "staticObj.h"

class pole : public staticObj {
public:
	using staticObj::staticObj;
	virtual void handleCollision(player& player, bool WhileFalling = false) override;
	virtual void handleCollision(enemy& enemy, bool WhileFalling = false) override;

private:
};