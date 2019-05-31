#ifndef IISLANDCLAIMCALLBACK_H
#define IISLANDCLAIMCALLBACK_H

class Player;
class IPlayerProvider;
class World;

class IIslandClaimCallback
{
	public:
		virtual ~IIslandClaimCallback() = default;

		virtual void invoke(Player *player, IPlayerProvider &playerProvider, World &world) = 0;
};

#endif // IISLANDCLAIMCALLBACK_H
