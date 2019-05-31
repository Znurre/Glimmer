#ifndef REVERSEDIRECTIONCLAIMCALLBACK_H
#define REVERSEDIRECTIONCLAIMCALLBACK_H

#include "IIslandClaimCallback.h"

class ReverseDirectionClaimCallback : public IIslandClaimCallback
{
	public:
		void invoke(Player *self, IPlayerProvider &playerProvider, World &world) override;
};

#endif // REVERSEDIRECTIONCLAIMCALLBACK_H
