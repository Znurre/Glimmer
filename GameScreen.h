#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "IScreen.h"
#include "IPlayerProvider.h"
#include "World.h"

class Stage;
class PlayerController;
class GameFieldScreen;
class IPlayerInputCallback;

class GameScreen
	: public IScreen
	, public IPlayerProvider
{
	public:
		GameScreen(Stage *stage, QVector<PlayerController *> players);
		~GameScreen() override;

		QVector<Player *> players() const override;

		void update(long delta) override;
		void draw(QPainter &painter) override;

		void keyPressed(QKeyEvent *event) override;
		void keyReleased(QKeyEvent *event) override;

		void gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button) override;
		void gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button) override;

	private:
		IPlayerInputCallback *resolveInputCallback(Player *player) const;

		QVector<Player *> m_players;
		QVector<PlayerController *> m_controllers;
		QVector<GameFieldScreen *> m_screens;

		Stage *m_stage;
		World m_world;

		long m_deadTimer;
};

#endif // GAMESCREEN_H
