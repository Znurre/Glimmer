#include <cmath>

#include "Player.h"
#include "World.h"

template<typename T>
T lerp(T start, T end, float value)
{
	return start + (end - start) * value;
}

Player::Player(World &world, const QColor &color)
	: m_world(world)
	, m_color(color)
	, m_elapsed(0)
	, m_direction(1)
	, m_score(0)
	, m_dead(false)
{
	m_path << QPoint();
}

void Player::place()
{
	if (m_dead)
	{
		return;
	}

	const QPoint &position = getPendingPoint();

	const int score = m_world.tryClaimIsland(position, m_color);

	if (score > 0)
	{
		m_score += score;

		m_path << position;

		m_elapsed = 0;
		m_direction = (qrand() % 2) ? -1 : 1;

		const int islandCount = (qrand() % 2) + 1;

		float offset = 0;

		for (int i = 0; i < islandCount; i++)
		{
			offset += m_world.createIsland(position, offset);
		}
	}
	else
	{
		m_dead = true;
	}
}

void Player::update(long delta)
{
	if (m_dead)
	{
		return;
	}

	m_elapsed += delta / 500.0f;
}

void Player::draw(QPainter &painter)
{
	painter.setPen(QPen(m_color, 5));
	painter.drawPolyline(m_path);

	const QPoint &point = getPendingPoint();

	painter.drawLine(m_path.last(), point);
}

void Player::reset()
{
	m_score = 0;
	m_dead = false;
	m_elapsed = 0;
	m_direction = 1;

	m_path.clear();
	m_path << QPoint();
}

QPoint Player::position() const
{
	const int count = m_path.count();

	if (count > 1)
	{
		return lerp(m_path[count - 2], m_path[count - 1], qMin(1.0f, m_elapsed));
	}

	return m_path.last();
}

int Player::score() const
{
	return m_score;
}

bool Player::isDead() const
{
	return m_dead;
}

QPoint Player::getPendingPoint() const
{
	const QPoint &position = m_path.last();

	const float direction = (m_elapsed * (0.5 + (m_score / 100.0f))) * m_direction;

	const int x = position.x() + sin(direction * M_PI) * 50;
	const int y = position.y() + cos(direction * M_PI) * 50;

	return QPoint(x, y);
}
