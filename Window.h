#ifndef WINDOW_H
#define WINDOW_H

#include <QElapsedTimer>
#include <QRasterWindow>

#include "Player.h"
#include "World.h"
#include "Stage.h"
#include "IPlayerProvider.h"

class Window : public QRasterWindow
{
	public:
		Window();

	private:
		void paintEvent(QPaintEvent *event) override;
		void keyPressEvent(QKeyEvent *event) override;

		QElapsedTimer m_timer;

		Stage m_stage;
};

#endif // WINDOW_H
