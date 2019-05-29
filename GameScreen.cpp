#include <QDebug>
#include <QtMath>

#include "GameScreen.h"
#include "Player.h"
#include "PlayerController.h"
#include "IInputMethod.h"
#include "Stage.h"
#include "PlayerSelectionScreen.h"
#include "GameFieldScreen.h"

GameScreen::GameScreen(Stage *stage, QVector<PlayerController *> players)
	: m_controllers(players)
	, m_stage(stage)
	, m_world(*this)
	, m_deadTimer(0)
{
	for (PlayerController *player : players)
	{
//		ViewportBoundsCalculator viewportBoundsCalculator;

//		m_screens << new GameFieldScreen(player, viewportBoundsCalculator, m_world, *this);

		m_players << new Player(m_world, *this, *player);
	}

	m_world.reset();
}

GameScreen::~GameScreen()
{
	qDeleteAll(m_players);
}

QVector<Player *> GameScreen::players() const
{
	return m_players;
}

void GameScreen::update(long delta)
{
	bool allPlayersDead = true;

	for (Player *player : m_players)
	{
		player->update(delta);

		allPlayersDead &= player->isDead();
	}

	if (allPlayersDead)
	{
		if ((m_deadTimer += delta) > 10000 && m_playersForRematch.count() < m_players.count())
		{
			return m_stage->changeScreen(new PlayerSelectionScreen(m_stage), 500.0f);
		}
	}

	m_world.update(delta);
}

void GameScreen::draw(QPainter &painter)
{
	int i = 0;

	const QRect &vp = painter.viewport();

	const int viewportWidth = vp.width() / m_players.count();

	for (Player *player : m_players)
	{
		const QRect scoreRect(-viewportWidth / 2, -vp.height() / 2, viewportWidth, 60 + player->rank() * 20);
		const QRect viewport(-viewportWidth / 2, -(vp.height() / 2 - scoreRect.height()), viewportWidth, vp.height() - scoreRect.height());

		static const QFont scoreFont("Bebas Neue", 30);

		painter.resetTransform();
		painter.setClipRect(vp);
		painter.translate(viewportWidth * i + (viewportWidth / 2), vp.height() / 2);
		painter.setPen(QPen(Qt::white, 2));
		painter.setFont(scoreFont);
		painter.fillRect(scoreRect, player->controller().color());
		painter.drawText(scoreRect, Qt::AlignCenter, QString::number(player->score()));
		painter.setClipRect(viewport);
		painter.fillRect(viewport, player->controller().color().dark(500));
		painter.translate(-player->position());

		m_world.draw(painter);

		for (Player *p : m_players)
		{
			if (p != player)
			{
				p->draw(painter);
			}
		}

		player->draw(painter);

		if (player->isDead())
		{
			static const QFont deadFont("Bebas Neue", 25);
			static const QFont instructionFont("Bebas Neue", 15);

			painter.translate(player->position());
			painter.fillRect(viewport, QColor(0, 0, 0, 150));
			painter.setFont(deadFont);
			painter.setPen(Qt::white);
			painter.drawText(viewport.translated(0, -30), Qt::AlignCenter, "You are dead");

			if (m_deadTimer > 0 && !m_playersForRematch.contains(player))
			{
				const QRect deathRect(viewport.x() + (viewportWidth - 250) / 2, viewport.y() + (viewport.height() - 250) / 2, 250, 250);

				const float opacity = qMin(1.0f, m_deadTimer / 300.0f);
				const float timeout = m_deadTimer / 10000.0f;

				painter.setOpacity(opacity);
				painter.setFont(instructionFont);
				painter.drawText(viewport.translated(0, 30), Qt::AlignCenter, "Press any key\nfor a rematch");
				painter.setPen(QPen(Qt::white, 10));
				painter.drawArc(deathRect, -(-90 + 360 * timeout) * 16, -360 * 16 * (1.0f - timeout));
				painter.setOpacity(1.0f);
			}
		}

		i++;
	}
}

void GameScreen::keyPressed(QKeyEvent *event)
{
	bool allPlayersDead = true;

	for (Player *player : m_players)
	{
		allPlayersDead &= player->isDead();

		if (player->controller().inputMethod()->isInput(event))
		{
			if (!player->isDead())
			{
				return player->place();
			}

			m_playersForRematch << player;
		}
	}

	if (m_playersForRematch.count() == m_players.count())
	{
		m_stage->changeScreen(new GameScreen(m_stage, m_controllers), 500.0f);
	}
}

void GameScreen::keyReleased(QKeyEvent *event)
{
	Q_UNUSED(event);
}

void GameScreen::gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button)
{
	Q_UNUSED(deviceId);
	Q_UNUSED(button);
}

void GameScreen::gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button)
{
	Q_UNUSED(deviceId);
	Q_UNUSED(button);
}
