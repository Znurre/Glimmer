#ifndef IPLAYERINPUTCALLBACK_H
#define IPLAYERINPUTCALLBACK_H

class Player;

class IPlayerInputCallback
{
	public:
		virtual ~IPlayerInputCallback() = default;

		virtual void invoke(Player *player) = 0;
};

#endif // IPLAYERINPUTCALLBACK_H
