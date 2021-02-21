#include "timePresent.h"

void timePresent::handleCollision(player& player, bool WhileFalling)
{
	if (getExistens())
		player.setPresentKind(addTime);
	setExistens(false);
	player.setNeedToFall(true);
}//end handleCollision with player

void timePresent::handleCollision(enemy& enemy, bool WhileFalling)
{
	enemy.setNeedToFall(true);
}//end handleCollision with enemy
