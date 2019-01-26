#ifndef ISCREEN_H
#define ISCREEN_H

#include <QKeyEvent>
#include <QGamepadManager>

class IScreen
{
	public:
		virtual ~IScreen() = default;

		virtual void update(long delta) = 0;
		virtual void draw(QPainter &painter) = 0;

		virtual void keyPressed(QKeyEvent *event) = 0;
		virtual void keyReleased(QKeyEvent *event) = 0;

		virtual void gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button) = 0;
		virtual void gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button) = 0;
};

#endif // ISCREEN_H
