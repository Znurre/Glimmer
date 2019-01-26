#ifndef STAGE_H
#define STAGE_H

#include "IScreen.h"

class Stage : public IScreen
{
	public:
		Stage();

		void update(long delta) override;
		void draw(QPainter &painter) override;

		void keyPressed(QKeyEvent *event) override;
		void keyReleased(QKeyEvent *event) override;

		void gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button) override;
		void gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button) override;

		void changeScreen(IScreen *next, long transitionLength);
		void changeScreen(IScreen *next);

	private:
		IScreen *m_current;
};

#endif // STAGE_H
