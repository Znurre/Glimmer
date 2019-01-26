#ifndef KEYBOARDINPUTMETHOD_H
#define KEYBOARDINPUTMETHOD_H

#include "IInputMethod.h"

class KeyboardInputMethod : public IInputMethod
{
	public:
		KeyboardInputMethod(QKeyEvent *event);

		QString symbol() const override;

		bool isInput(QKeyEvent *event) const override;
		bool isInput(int deviceId, QGamepadManager::GamepadButton button) const override;

	private:
		int m_key;
};

#endif // KEYBOARDINPUTMETHOD_H
