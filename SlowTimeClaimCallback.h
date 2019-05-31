#ifndef SLOWTIMECLAIMCALLBACK_H
#define SLOWTIMECLAIMCALLBACK_H

#include "IIslandClaimCallback.h"

class SlowTimeClaimCallback : public IIslandClaimCallback
{
	public:
		void invoke(Player *player, IPlayerProvider &playerProvider, World &world) override;
};

#endif // SLOWTIMECLAIMCALLBACK_H
