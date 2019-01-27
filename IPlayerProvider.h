#ifndef IPLAYERPROVIDER_H
#define IPLAYERPROVIDER_H

#include <QVector>

class Player;

class IPlayerProvider
{
	public:
		virtual QVector<Player *> players() const = 0;
};

#endif // IPLAYERPROVIDER_H
