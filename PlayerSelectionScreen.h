#ifndef PLAYERSELECTIONSCREEN_H
#define PLAYERSELECTIONSCREEN_H

#include <QColor>

#include "IScreen.h"
#include "PlayerController.h"

class Stage;

class PlayerSelectionScreen : public IScreen
{
	public:
		PlayerSelectionScreen(Stage *stage);

		void update(long delta) override;
		void draw(QPainter &painter) override;

		void keyPressed(QKeyEvent *event) override;
		void keyReleased(QKeyEvent *event) override;

		void gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button) override;
		void gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button) override;

	private:
		Stage *m_stage;

		QVector<PlayerController *> m_players;

		float m_renderedPlayers;
		float m_elapsed;
};

#endif // PLAYERSELECTIONSCREEN_H
