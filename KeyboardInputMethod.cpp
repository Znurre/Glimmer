#include "KeyboardInputMethod.h"

KeyboardInputMethod::KeyboardInputMethod(QKeyEvent *event)
	: m_key(event->key())
{
}

QString KeyboardInputMethod::symbol() const
{
	return "⌨";
}

bool KeyboardInputMethod::isInput(QKeyEvent *event) const
{
	return event->key() == m_key;
}

bool KeyboardInputMethod::isInput(int deviceId, QGamepadManager::GamepadButton button) const
{
	Q_UNUSED(deviceId);
	Q_UNUSED(button);

	return false;
}
