#include <QPainter>
#include <QKeyEvent>

#include "Window.h"

Window::Window()
{
	static QList<QColor> colors =
	{
		Qt::red,
		Qt::blue,
		Qt::yellow
	};

	for (int i = 0; i < 3; i++)
	{
		m_players << new Player(m_world, colors[i]);
	}

	m_timer.start();

	m_world.reset();
}

void Window::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.fillRect(event->rect(), Qt::black);

	if (m_timer.elapsed())
	{
		const long delta = m_timer.restart();

		for (Player *player : m_players)
		{
			player->update(delta);
		}

		m_world.update(delta);
	}

	int i = 0;

	const int viewportWidth = width() / m_players.count();

	for (Player *player : m_players)
	{
		painter.resetTransform();

		const QRect viewport(viewportWidth * i, 0, viewportWidth, height());

		painter.setClipRect(viewport);

		painter.translate(viewportWidth * i + (viewportWidth / 2), height() / 2);
		painter.setPen(QPen(Qt::white, 2));
		painter.drawText(QRect(10, 10 - height() / 2, 100, 20), QString::number(player->score()));
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

	update();
}

void Window::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control)
	{
		m_players[0]->place();
	}

	if (event->key() == Qt::Key_Space)
	{
		m_players[1]->place();
	}

	if (event->key() == Qt::Key_Enter)
	{
		m_players[2]->place();
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
