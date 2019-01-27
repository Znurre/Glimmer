#include "GameScreen.h"
#include "Player.h"
#include "PlayerController.h"
#include "IInputMethod.h"

GameScreen::GameScreen(Stage *stage, QVector<PlayerController *> players)
	: m_world(*this)
{
	Q_UNUSED(stage);
	Q_UNUSED(players);

	static QList<QColor> colors =
	{
		Qt::red,
		Qt::blue,
		Qt::yellow
	};

	for (PlayerController *player : players)
	{
		m_players << new Player(m_world, *this, player);
	}

	m_world.reset();
}

QVector<Player *> GameScreen::players() const
{
	return m_players;
}

void GameScreen::update(long delta)
{
	for (Player *player : m_players)
	{
		player->update(delta);
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
		painter.fillRect(scoreRect, player->controller()->color());
		painter.drawText(scoreRect, Qt::AlignCenter, QString::number(player->score()));
		painter.setClipRect(viewport);
		painter.fillRect(viewport, player->controller()->color().dark(500));
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

		i++;
	}
}

void GameScreen::keyPressed(QKeyEvent *event)
{
	for (Player *player : m_players)
	{
		if (player->controller()->inputMethod()->isInput(event))
		{
			return player->place();
		}
	}

	if (event->key() == Qt::Key_Return)
	{
		for (Player *player : m_players)
		{
			if (!player->isDead())
			{
				return;
			}
		}

		for (Player *player : m_players)
		{
			player->reset();
		}

		m_world.reset();
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
