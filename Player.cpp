#include <cmath>

#include <QDebug>

#include "Player.h"
#include "World.h"
#include "Utility.h"
#include "PlayerController.h"
#include "IPlayerProvider.h"
#include "IIslandClaimCallback.h"

Player::Player(World &world
	, IPlayerProvider &playerProvider
	, PlayerController &controller
	)
	: m_controller(controller)
	, m_world(world)
	, m_playerProvider(playerProvider)
	, m_elapsed(0)
	, m_rankTimer(0)
	, m_direction(1)
	, m_score(0)
	, m_rank(0)
	, m_previousRank(0)
	, m_combo(0)
	, m_count(0)
	, m_spawnIslands(0)
	, m_slowDown(0)
	, m_dead(false)
	, m_rematch(false)
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

	const auto callback = m_world.tryClaimIsland(position, m_controller.color(), m_spawnIslands-- > 0);

	if (callback)
	{
		callback->invoke(this, m_playerProvider, m_world);

		m_combo++;
		m_count++;

		m_path << position;

		m_elapsed = 0;
		m_direction = -m_direction;
		m_slowDown--;

		const int islandCount = (qrand() % 2) + 1;

		float offset = 0;

		for (int i = 0; i < islandCount; i++)
		{
			offset += m_world.createIsland(position, offset);
		}

		delete callback;
	}
	else
	{
		m_dead = true;
	}
}

void Player::rematch()
{
	m_rematch = true;
}

void Player::addScore(int score)
{
	m_score += score;
}

void Player::reverse()
{
	m_direction = m_direction > 0 ? -1 : 1;
}

void Player::spawnIslands()
{
	m_spawnIslands = 3;
}

void Player::slowDown()
{
	m_slowDown = 3;
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

	if (getAngle() > 2)
	{
		m_combo = 0;
	}
}

void Player::draw(QPainter &painter)
{
	painter.setPen(QPen(m_controller.color(), 5));
	painter.setBrush(m_controller.color());
	painter.drawEllipse(m_path.first(), 5, 5);
	painter.setBrush(Qt::NoBrush);
	painter.drawPolyline(m_path);

	const QPoint &point = getPendingPoint();

	if (m_dead || m_spawnIslands > 0)
	{
		painter.drawEllipse(point, 5, 5);
	}

	painter.drawLine(m_path.last(), point);
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

int Player::combo() const
{
	return m_combo / 15;
}

bool Player::isDead() const
{
	return m_dead;
}

bool Player::rematchRequested() const
{
	return m_rematch;
}

float Player::rank() const
{
	return lerp((float)m_previousRank, (float)m_rank, qMin(1.0f, m_rankTimer));
}

float Player::getAngle() const
{
	return m_elapsed * (0.5 + (m_count / 100.0f)) * (m_slowDown > 0 ? 0.5 : 1);
}

QPoint Player::getPendingPoint() const
{
	const QPoint &position = m_path.last();

	const float direction = getAngle() * m_direction;

	const int x = position.x() + sin(direction * M_PI) * 50;
	const int y = position.y() + cos(direction * M_PI) * 50;

	return QPoint(x, y);
}
