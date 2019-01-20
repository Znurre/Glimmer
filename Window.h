#ifndef WINDOW_H
#define WINDOW_H

#include <QElapsedTimer>
#include <QRasterWindow>

#include "Player.h"
#include "World.h"

class Window : public QRasterWindow
{
	public:
		Window();

	private:
		void paintEvent(QPaintEvent *event) override;
		void keyPressEvent(QKeyEvent *event) override;

		QElapsedTimer m_timer;
		QVector<Player *> m_players;

		World m_world;
};

#endif // WINDOW_H
