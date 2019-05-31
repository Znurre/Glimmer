#include "SlowTimeClaimCallback.h"
#include "Player.h"
#include "IPlayerProvider.h"

void SlowTimeClaimCallback::invoke(Player *player, IPlayerProvider &playerProvider, World &world)
{
	Q_UNUSED(playerProvider)
	Q_UNUSED(world)

	for (Player *p : playerProvider.players())
	{
		if (p != player)
		{
			p->slowDown();
		}
	}
}
