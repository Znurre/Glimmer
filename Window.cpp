#include <QPainter>
#include <QKeyEvent>
#include <QGamepadManager>
#include <QGamepad>
#include <QFont>

#include "Window.h"

Window::Window()
{
	m_timer.start();
}

void Window::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.fillRect(event->rect(), "#212526");

	if (m_timer.elapsed())
	{
		const long delta = m_timer.restart();

		m_stage.update(delta);
	}

	m_stage.draw(painter);

	update();
}

void Window::keyPressEvent(QKeyEvent *event)
{
	m_stage.keyPressed(event);
}
