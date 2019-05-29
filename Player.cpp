#include <cmath>

#include "Player.h"
#include "World.h"
#include "Utility.h"
#include "PlayerController.h"
#include "IPlayerProvider.h"

Player::Player(World &world, IPlayerProvider &playerProvider, PlayerController &controller)
	: m_controller(controller)
	, m_world(world)
	, m_playerProvider(playerProvider)
	, m_elapsed(0)
	, m_rankTimer(0)
	, m_direction(1)
	, m_score(0)
	, m_rank(0)
	, m_previousRank(0)
	, m_dead(false)
{
	m_path << QPoint();
}

PlayerController &Player::controller() const
{
	return m_controller;
}

void Player::place()
{
	if (m_dead)
	{
		return;
	}

	const QPoint &position = getPendingPoint();

	const int score = m_world.tryClaimIsland(position, m_controller.color());

	if (score > 0)
	{
		m_score += score;

		m_path << position;

		m_elapsed = 0;
		m_direction = -m_direction;

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
	int rank = 0;

	for (Player *player : m_playerProvider.players())
	{
		if (m_score > player->score())
		{
			rank++;
		}
	}

	if (rank != m_rank)
	{
		m_rankTimer = 0;

		m_previousRank = m_rank;
		m_rank = rank;
	}

	m_rankTimer += delta / 500.0f;

	if (m_dead)
	{
		return;
	}

	m_elapsed += delta / 500.0f;
}

void Player::draw(QPainter &painter)
{
	painter.setPen(QPen(m_controller.color(), 5));
	painter.setBrush(m_controller.color());
	painter.drawEllipse(m_path.first(), 5, 5);
	painter.setBrush(Qt::NoBrush);
	painter.drawPolyline(m_path);

	const QPoint &point = getPendingPoint();

	if (m_dead)
	{
		painter.drawEllipse(point, 5, 5);
	}

	painter.drawLine(m_path.last(), point);
}

void Player::reset()
{
	m_score = 0;
	m_dead = false;
	m_elapsed = 0;
	m_direction = 1;
	m_rank = 0;
	m_previousRank = 0;

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

float Player::rank() const
{
	return lerp((float)m_previousRank, (float)m_rank, qMin(1.0f, m_rankTimer));
}

QPoint Player::getPendingPoint() const
{
	const QPoint &position = m_path.last();

	const float direction = (m_elapsed * (0.5 + (m_score / 100.0f))) * m_direction;

	const int x = position.x() + sin(direction * M_PI) * 50;
	const int y = position.y() + cos(direction * M_PI) * 50;

	return QPoint(x, y);
}
