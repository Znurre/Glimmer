#include "LowerScoreClaimCallback.h"
#include "World.h"

void LowerScoreClaimCallback::invoke(Player *player, IPlayerProvider &playerProvider, World &world)
{
	Q_UNUSED(player)
	Q_UNUSED(playerProvider)

	world.lowerScores();
}
