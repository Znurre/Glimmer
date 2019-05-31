#include "SlowTimeClaimCallback.h"
#include "Player.h"

void SlowTimeClaimCallback::invoke(Player *player, IPlayerProvider &playerProvider, World &world)
{
	Q_UNUSED(playerProvider)
	Q_UNUSED(world)

	player->slowDown();
}
