#include "badPresent.h"

void badPresent::handleCollision(player& player, bool WhileFalling)
{
	if (getExistens())
		player.setPresentKind(addEnemy);
	setExistens(false);
	player.setNeedToFall(true);
}//end handleCollision with player

void badPresent::handleCollision(enemy& enemy, bool WhileFalling)
{
	enemy.setNeedToFall(true);
}//end handleCollision with enemy
