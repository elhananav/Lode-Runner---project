#include "pole.h"
#include "player.h"

void pole::handleCollision(player& player, bool WhileFalling)
{
	player.handleCollision(*this, WhileFalling);
}//end handleCollision with player

void pole::handleCollision(enemy& enemy, bool WhileFalling)
{
	enemy.handleCollision(*this, WhileFalling);
}//end handleCollision with enemy
