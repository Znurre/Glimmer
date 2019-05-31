#ifndef LOWERSCORECLAIMCALLBACK_H
#define LOWERSCORECLAIMCALLBACK_H

#include "IIslandClaimCallback.h"

class LowerScoreClaimCallback : public IIslandClaimCallback
{
	public:
		void invoke(Player *player, IPlayerProvider &playerProvider, World &world) override;
};

#endif // LOWERSCORECLAIMCALLBACK_H
