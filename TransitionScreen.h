#ifndef TRANSITIONSCREEN_H
#define TRANSITIONSCREEN_H

#include "IScreen.h"

class Stage;

class TransitionScreen : public IScreen
{
	public:
		TransitionScreen(Stage *stage, IScreen *current, IScreen *next, float duration);
		~TransitionScreen();

		void update(long delta) override;
		void draw(QPainter &painter) override;

		void keyPressed(QKeyEvent *event) override;
		void keyReleased(QKeyEvent *event) override;

		void gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button) override;
		void gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button) override;

	private:
		IScreen *getCurrentScreen() const;

		Stage *m_stage;

		IScreen *m_current;
		IScreen *m_next;

		float m_duration;
		float m_remaining;
};

#endif // TRANSITIONSCREEN_H
