#include <cmath>

#include <QPainter>

#include "TransitionScreen.h"
#include "Stage.h"

TransitionScreen::TransitionScreen(Stage *stage, IScreen *current, IScreen *next, float duration)
	: m_stage(stage)
	, m_current(current)
	, m_next(next)
	, m_duration(duration)
	, m_remaining(duration)
{
}

TransitionScreen::~TransitionScreen()
{
	delete m_current;
}

void TransitionScreen::update(long delta)
{
	if ((m_remaining -= delta) <= 0)
	{
		m_stage->changeScreen(m_next);
	}
}

void TransitionScreen::draw(QPainter &painter)
{
	IScreen *screen = getCurrentScreen();

	screen->draw(painter);

	const float progress = std::max(0.0f, m_remaining / m_duration);
	const float alpha = sin(progress * M_PI);

	const QRect &viewport = painter.viewport();

	painter.resetTransform();
	painter.setClipRect(viewport);
	painter.setOpacity(alpha);
	painter.fillRect(viewport, Qt::black);
	painter.setOpacity(1.0f);
}

void TransitionScreen::keyPressed(QKeyEvent *event)
{
	Q_UNUSED(event);
}

void TransitionScreen::keyReleased(QKeyEvent *event)
{
	Q_UNUSED(event);
}

void TransitionScreen::gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button)
{
	Q_UNUSED(deviceId);
	Q_UNUSED(button);
}

void TransitionScreen::gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button)
{
	Q_UNUSED(deviceId);
	Q_UNUSED(button);
}

IScreen *TransitionScreen::getCurrentScreen() const
{
	if (m_remaining <= (m_duration / 2))
	{
		return m_next;
	}

	return m_current;
}
