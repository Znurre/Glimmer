#ifndef WORLD_H
#define WORLD_H

#include <cmath>

#include <QPoint>
#include <QVector>
#include <QPainter>
#include <QSet>

class Island;
class IPlayerController;

class World
{
	public:
		World(IPlayerController &playerController);

		float createIsland(const QPoint &origin, float offset);

		void update(long delta);
		void draw(QPainter &painter);
		void reset();

		int tryClaimIsland(const QPoint &point, const QColor &color);

	private:
		IPlayerController &m_playerController;

		QSet<Island *> m_unclaimedIslands;
		QVector<Island *> m_islands;
};

#endif // WORLD_H
