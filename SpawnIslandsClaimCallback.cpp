#include "SpawnIslandsClaimCallback.h"
#include "Player.h"

void SpawnIslandsClaimCallback::invoke(Player *player, IPlayerProvider &playerProvider, World &world)
{
	Q_UNUSED(playerProvider)
	Q_UNUSED(world)

	player->spawnIslands();
}
