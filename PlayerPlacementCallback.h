#ifndef PLAYERPLACEMENTCALLBACK_H
#define PLAYERPLACEMENTCALLBACK_H

#include "IPlayerInputCallback.h"

class Player;

class PlayerPlacementCallback : public IPlayerInputCallback
{
	public:
		void invoke(Player *player) override;
};

#endif // PLAYERPLACEMENTCALLBACK_H
