#ifndef PLAYER_H
#define PLAYER_H

#include <QPoint>
#include <QPolygon>
#include <QPainter>

class World;
class PlayerController;

class Player : public QObject
{
	public:
		Player(World &world, PlayerController *controller);

		void place();

		void update(long delta);
		void draw(QPainter &painter);
		void reset();

		QPoint position() const;

		int score() const;

		bool isDead() const;

	private:
		QPoint getPendingPoint() const;

		PlayerController *m_controller;

		World &m_world;

		QPolygon m_path;

		float m_elapsed;

		int m_direction;
		int m_score;

		bool m_dead;
};

#endif // PLAYER_H
