#ifndef IINPUTMETHOD_H
#define IINPUTMETHOD_H

#include <QGamepadManager>
#include <QKeyEvent>
#include <QString>

class IInputMethod
{
	public:
		virtual ~IInputMethod() = default;

		virtual QString symbol() const = 0;

		virtual bool isInput(QKeyEvent *event) const = 0;
		virtual bool isInput(int deviceId, QGamepadManager::GamepadButton button) const = 0;
};

#endif // IINPUTMETHOD_H
