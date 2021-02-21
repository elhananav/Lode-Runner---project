#include "lifePresent.h"

void lifePresent::handleCollision(player& player, bool WhileFalling)
{
	if (getExistens())
		player.setPresentKind(addLife);
	setExistens(false);
	player.setNeedToFall(true);
}//end handleCollision with player

void lifePresent::handleCollision(enemy& enemy, bool WhileFalling)
{
	enemy.setNeedToFall(true);
}//end handleCollision with enemy

