#include <QPainter>
#include <QDebug>

#include "PlayerSelectionScreen.h"
#include "Utility.h"
#include "Stage.h"
#include "GameScreen.h"
#include "KeyboardInputMethod.h"

PlayerSelectionScreen::PlayerSelectionScreen(Stage *stage)
	: m_stage(stage)
	, m_renderedPlayers(0)
	, m_elapsed(0)
{
}

void PlayerSelectionScreen::update(long delta)
{
	m_elapsed += delta / 1000.0f;
	m_renderedPlayers = lerp(m_renderedPlayers, (float)m_players.count(), qMin(1.0f, m_elapsed));
}

void PlayerSelectionScreen::draw(QPainter &painter)
{
	static const QFont smallFont("Bebas Neue", 20);
	static const QFont largeFont("Bebas Neue", 30);
	static const QFont hugeFont("Bebas Neue", 50);
	static const QFont fontAwesome("Font Awesome", 50);

//	static const QColor background("#212526");
	static const QColor foreground("#4B6776");

	QRect viewport = painter.viewport();

	const int stripWidth = viewport.width() / 4.0f;

	for (int i = 0; i < m_players.count(); i++)
	{
		PlayerController *player = m_players[i];

		const QRect playerRect(i * stripWidth, 0, stripWidth, viewport.height());

		painter.setPen(QPen(Qt::white, 2));
		painter.fillRect(playerRect, player->color());

		painter.setFont(fontAwesome);
		painter.drawText(playerRect.translated(0, -50), Qt::AlignCenter, player->inputMethod()->symbol());

		if (player->isReady())
		{
			painter.setFont(hugeFont);
			painter.drawText(playerRect.translated(0, 50), Qt::AlignCenter, "Ready!");
		}
		else
		{
			painter.setFont(smallFont);
			painter.drawText(playerRect.translated(0, 50), Qt::AlignCenter, "Press again\nto ready yourself");
		}
	}

	viewport.setX(m_renderedPlayers * stripWidth);

	painter.setFont(largeFont);
	painter.setPen(QPen(foreground, 2));
	painter.drawText(viewport, Qt::AlignCenter, "Press any key\nor gamepad button\nto join the game");
}

void PlayerSelectionScreen::keyPressed(QKeyEvent *event)
{
	bool allReady = true;
	bool inputHandled = false;

	for (PlayerController *player : m_players)
	{
		if (player->inputMethod()->isInput(event))
		{
			player->toggleReady();

			inputHandled = true;
		}

		allReady &= player->isReady();
	}

	if (inputHandled)
	{
		if (allReady)
		{
			m_stage->changeScreen(new GameScreen(m_stage, m_players), 1000.0f);
		}

		return;
	}

	if (m_players.count() == 4)
	{
		return;
	}

	static QVector<QColor> colors =
	{
		"#f47750",
		"#3daee9",
		"#fdbc4b",
		"#9b59b6"
	};

	m_players << new PlayerController(colors[m_players.count()], new KeyboardInputMethod(event));

	m_elapsed = 0;
}

void PlayerSelectionScreen::keyReleased(QKeyEvent *event)
{
	Q_UNUSED(event);
}

void PlayerSelectionScreen::gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button)
{
	Q_UNUSED(deviceId);
	Q_UNUSED(button);
}

void PlayerSelectionScreen::gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button)
{
	Q_UNUSED(deviceId);
	Q_UNUSED(button);
}
