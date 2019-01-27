#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "IScreen.h"
#include "IPlayerProvider.h"
#include "World.h"

class Stage;
class PlayerController;

class GameScreen : public IScreen, public IPlayerProvider
{
	public:
		GameScreen(Stage *stage, QVector<PlayerController *> players);

		QVector<Player *> players() const override;

		void update(long delta) override;
		void draw(QPainter &painter) override;

		void keyPressed(QKeyEvent *event) override;
		void keyReleased(QKeyEvent *event) override;

		void gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button) override;
		void gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button) override;

	private:
		QVector<Player *> m_players;

		World m_world;
};

#endif // GAMESCREEN_H
