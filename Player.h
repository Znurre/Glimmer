#ifndef PLAYER_H
#define PLAYER_H

#include <QPoint>
#include <QPolygon>
#include <QPainter>

class World;

class Player
{
	public:
		Player(World &world, const QColor &color);

		void place();

		void update(long delta);
		void draw(QPainter &painter);
		void reset();

		QPoint position() const;

		int score() const;

		bool isDead() const;

	private:
		QPoint getPendingPoint() const;

		World &m_world;

		QPolygon m_path;
		QColor m_color;

		float m_elapsed;

		int m_direction;
		int m_score;

		bool m_dead;
};

#endif // PLAYER_H
