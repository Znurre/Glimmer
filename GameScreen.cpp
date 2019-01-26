#include "GameScreen.h"
#include "Player.h"

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
		m_players << new Player(m_world, player);
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
		painter.resetTransform();

		const QRect viewport(viewportWidth * i, 0, viewportWidth, vp.height());

		static const QFont scoreFont("sans", 40, 70);

		painter.setClipRect(viewport);
		painter.translate(viewportWidth * i + (viewportWidth / 2), vp.height() / 2);
		painter.setPen(QPen(Qt::white, 2));
		painter.setFont(scoreFont);
		painter.drawText(QRect(10, 10 - vp.height() / 2, 100, 60), QString::number(player->score()));
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
//	if (event->key() == Qt::Key_Control)
//	{
//		m_players[0]->place();
//	}

	if (event->key() == Qt::Key_Space)
	{
		m_players[0]->place();
	}

	if (event->key() == Qt::Key_Enter)
	{
		m_players[1]->place();
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
