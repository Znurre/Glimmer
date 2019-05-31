#ifndef SPAWNISLANDSCLAIMCALLBACK_H
#define SPAWNISLANDSCLAIMCALLBACK_H

#include "IIslandClaimCallback.h"

class SpawnIslandsClaimCallback : public IIslandClaimCallback
{
	public:
		void invoke(Player *player, IPlayerProvider &playerProvider, World &world) override;
};

#endif // SPAWNISLANDSCLAIMCALLBACK_H
