#ifndef IPLAYERCONTROLLER_H
#define IPLAYERCONTROLLER_H

#include <QVector>

class Player;

class IPlayerController
{
	public:
		virtual QVector<Player *> players() const = 0;
};

#endif // IPLAYERCONTROLLER_H
