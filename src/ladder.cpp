#include "ladder.h"

void ladder::handleCollision(player& player, bool WhileFalling)
{
	player.handleCollision(*this, WhileFalling);
}//end handleCollision with player

void ladder::handleCollision(enemy& enemy, bool WhileFalling)
{
	enemy.handleCollision(*this, WhileFalling);
}//end handleCollision with enemy
