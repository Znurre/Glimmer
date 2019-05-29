#ifndef PLAYER_H
#define PLAYER_H

#include <QPoint>
#include <QPolygon>
#include <QPainter>

class World;
class PlayerController;
class IPlayerProvider;

class Player : public QObject
{
	public:
		Player(World &world, IPlayerProvider &playerProvider, PlayerController &controller);

		PlayerController &controller() const;

		void place();

		void update(long delta);
		void draw(QPainter &painter);
		void reset();

		QPoint position() const;

		int score() const;

		bool isDead() const;

		float rank() const;

	private:
		QPoint getPendingPoint() const;

		PlayerController &m_controller;

		World &m_world;
		IPlayerProvider &m_playerProvider;

		QPolygon m_path;

		float m_elapsed;
		float m_rankTimer;

		int m_direction;
		int m_score;
		int m_rank;
		int m_previousRank;

		bool m_dead;
};

#endif // PLAYER_H
