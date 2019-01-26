#include "Stage.h"
#include "PlayerSelectionScreen.h"
#include "GameScreen.h"
#include "TransitionScreen.h"

Stage::Stage()
	: m_current(new PlayerSelectionScreen(this))
{
}

void Stage::update(long delta)
{
	m_current->update(delta);
}

void Stage::draw(QPainter &painter)
{
	m_current->draw(painter);
}

void Stage::keyPressed(QKeyEvent *event)
{
	m_current->keyPressed(event);
}

void Stage::keyReleased(QKeyEvent *event)
{
	m_current->keyReleased(event);
}

void Stage::gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button)
{
	m_current->gamepadButtonPressed(deviceId, button);
}

void Stage::gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button)
{
	m_current->gamepadButtonReleased(deviceId, button);
}

void Stage::changeScreen(IScreen *next, long transitionLength)
{
	m_current = new TransitionScreen(this, m_current, next, transitionLength);
}

void Stage::changeScreen(IScreen *next)
{
	delete m_current;

	m_current = next;
}
