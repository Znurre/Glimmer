#include <QVector2D>
#include <QMap>

#include <cmath>

#include "World.h"
#include "Island.h"
#include "IPlayerProvider.h"

World::World(IPlayerProvider &playerController)
	: m_playerController(playerController)
{
}

float World::createIsland(const QPoint &origin, float offset)
{
	const float direction = (qrand() % 100) / 100.0f + offset;

	const int size = (qrand() % 20) + 10;
	const int x = origin.x() + sin(direction * M_PI) * 50;
	const int y = origin.y() - abs(cos(direction * M_PI) * 50);

	Island *island = new Island(QPoint(x, y), size);

	m_islands << island;
	m_unclaimedIslands << island;

	const float circumference = M_PI * (50 * 2);
	const float occupied = size / circumference;

	return direction + occupied * (M_PI * 2);
}

void World::update(long delta)
{
	for (Island *island : m_islands)
	{
		island->update(delta);
	}
}

void World::draw(QPainter &painter)
{
	for (Island *island : m_islands)
	{
		island->draw(painter, m_unclaimedIslands.contains(island));
	}
}

void World::reset()
{
	m_islands.clear();
	m_unclaimedIslands.clear();

	const QVector<Player *> &players = m_playerController.players();

	for (int i = 0; i < players.count(); i++)
	{
		createIsland(QPoint(), i);
	}
}

int World::tryClaimIsland(const QPoint &point, const QColor &color)
{
	QMap<float, Island *> islandsByDistance;

	for (Island *island : m_unclaimedIslands)
	{
		const QVector2D vector(point - island->position());

		const float length = vector.length();

		if (length <= island->size())
		{
			islandsByDistance[length] = island;
		}
	}

	for (Island *island : islandsByDistance)
	{
		m_unclaimedIslands.remove(island);

		return island->claim(color);
	}

	return -1;
}
