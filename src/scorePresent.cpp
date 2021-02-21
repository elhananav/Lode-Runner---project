#include "scorePresent.h"

void scorePresent::handleCollision(player& player, bool WhileFalling)
{
	if (getExistens())
		player.setPresentKind(addScore);
	setExistens(false);
	player.setNeedToFall(true);
}//end handleCollision with player

void scorePresent::handleCollision(enemy& enemy, bool WhileFalling)
{
	enemy.setNeedToFall(true);
}//end handleCollision with enemy
