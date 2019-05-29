#include "GameFieldScreen.h"
#include "Player.h"
#include "IPlayerProvider.h"
#include "World.h"
#include "PlayerController.h"
#include "ViewportBoundsCalculator.h"

GameFieldScreen::GameFieldScreen(PlayerController &controller, ViewportBoundsCalculator &viewportBoundsCalculator, World &world, IPlayerProvider &playerProvider)
	: m_player(world, playerProvider, controller)
	, m_controller(controller)
	, m_viewportBoundsCalculator(viewportBoundsCalculator)
	, m_world(world)
	, m_playerProvider(playerProvider)
{
}

void GameFieldScreen::update(long delta)
{
	m_player.update(delta);
}

void GameFieldScreen::draw(QPainter &painter)
{
	const auto &viewport = m_viewportBoundsCalculator.calculate(painter);

	const QRect scoreFrameBounds(0, 0, viewport.width(), int(60 + m_player.rank() * 20));
	const QRect gameFieldBounds(scoreFrameBounds.bottomLeft(), viewport.bottomRight());

	static const QFont scoreFont("Bebas Neue", 30);

	painter.resetTransform();
	painter.setPen(QPen(Qt::white, 2));
	painter.setFont(scoreFont);
	painter.fillRect(scoreFrameBounds, m_controller.color());
	painter.drawText(scoreFrameBounds, Qt::AlignCenter, QString::number(m_player.score()));
	painter.setClipRect(viewport);
	painter.fillRect(viewport, m_controller.color().dark(500));
	painter.setClipRect(gameFieldBounds);
	painter.translate(-m_player.position());

	m_world.draw(painter);

	for (Player *player : m_playerProvider.players())
	{
		if (player != &m_player)
		{
			player->draw(painter);
		}
	}

	m_player.draw(painter);

	if (m_player.isDead())
	{
		static const QFont deadFont("Bebas Neue", 25);
		static const QFont instructionFont("Bebas Neue", 15);

		painter.translate(m_player.position());
		painter.fillRect(viewport, QColor(0, 0, 0, 150));
		painter.setFont(deadFont);
		painter.setPen(Qt::white);
		painter.drawText(viewport.translated(0, -30), Qt::AlignCenter, "You are dead");

//		if (m_deadTimer > 0 && !m_playersForRematch.contains(player))
//		{
//			const QRect deathRect(viewport.x() + (viewportWidth - 250) / 2, viewport.y() + (viewport.height() - 250) / 2, 250, 250);

//			const float opacity = qMin(1.0f, m_deadTimer / 300.0f);
//			const float timeout = m_deadTimer / 10000.0f;

//			painter.setOpacity(opacity);
//			painter.setFont(instructionFont);
//			painter.drawText(viewport.translated(0, 30), Qt::AlignCenter, "Press any key\nfor a rematch");
//			painter.setPen(QPen(Qt::white, 10));
//			painter.drawArc(deathRect, -(-90 + 360 * timeout) * 16, -360 * 16 * (1.0f - timeout));
//			painter.setOpacity(1.0f);
//		}
	}
}

void GameFieldScreen::keyPressed(QKeyEvent *event)
{
	Q_UNUSED(event)
}

void GameFieldScreen::keyReleased(QKeyEvent *event)
{
	Q_UNUSED(event)
}

void GameFieldScreen::gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button)
{
	Q_UNUSED(deviceId)
	Q_UNUSED(button)
}

void GameFieldScreen::gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button)
{
	Q_UNUSED(deviceId)
	Q_UNUSED(button)
}
