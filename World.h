#ifndef WORLD_H
#define WORLD_H

#include <cmath>

#include <QPoint>
#include <QVector>
#include <QPainter>
#include <QSet>

class Island;
class IPlayerProvider;

class World
{
	public:
		World(IPlayerProvider &playerController);

		float createIsland(const QPoint &origin, float offset);

		void update(long delta);
		void draw(QPainter &painter);
		void reset();

		int tryClaimIsland(const QPoint &point, const QColor &color);

	private:
		IPlayerProvider &m_playerController;

		QSet<Island *> m_unclaimedIslands;
		QVector<Island *> m_islands;
};

#endif // WORLD_H
