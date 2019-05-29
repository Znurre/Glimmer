#ifndef GAMEFIELDSCREEN_H
#define GAMEFIELDSCREEN_H

#include "IScreen.h"
#include "Player.h"

class PlayerController;
class ViewportBoundsCalculator;
class World;
class IPlayerProvider;

class GameFieldScreen : public IScreen
{
	public:
		GameFieldScreen(PlayerController &controller, ViewportBoundsCalculator &viewportBoundsCalculator, World &world, IPlayerProvider &playerProvider);

		void update(long delta) override;
		void draw(QPainter &painter) override;

		void keyPressed(QKeyEvent *event) override;
		void keyReleased(QKeyEvent *event) override;

		void gamepadButtonPressed(int deviceId, QGamepadManager::GamepadButton button) override;
		void gamepadButtonReleased(int deviceId, QGamepadManager::GamepadButton button) override;

	private:
		int m_index;

		Player m_player;

		PlayerController &m_controller;
		ViewportBoundsCalculator &m_viewportBoundsCalculator;
		World &m_world;
		IPlayerProvider &m_playerProvider;
};

#endif // GAMEFIELDSCREEN_H
