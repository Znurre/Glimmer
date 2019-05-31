#include "ReverseDirectionClaimCallback.h"
#include "IPlayerProvider.h"
#include "Player.h"

void ReverseDirectionClaimCallback::invoke(Player *self, IPlayerProvider &playerProvider, World &world)
{
	Q_UNUSED(world)

	for (Player *player : playerProvider.players())
	{
		if (player != self)
		{
			player->reverse();
		}
	}
}
