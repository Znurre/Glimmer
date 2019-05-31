#ifndef PLAYERREMATCHCALLBACK_H
#define PLAYERREMATCHCALLBACK_H

#include "IPlayerInputCallback.h"

class Player;

class PlayerRematchCallback : public IPlayerInputCallback
{
	public:
		void invoke(Player *player) override;
};

#endif // PLAYERREMATCHCALLBACK_H
