#ifndef ISLAND_H
#define ISLAND_H

#include <QPoint>
#include <QColor>
#include <QPainter>

class Island
{
	public:
		Island(const QPoint &position, int size);

		QPoint position() const;

		int size() const;
		int score() const;

		int claim(const QColor &color);

		void update(long delta);
		void draw(QPainter &painter, bool unclaimed);

	private:
		QPoint m_position;
		QColor m_color;

		int m_size;

		float m_ripple;

		bool m_claimed;
};

#endif // ISLAND_H
