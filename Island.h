#ifndef ISLAND_H
#define ISLAND_H

#include <QPoint>
#include <QColor>
#include <QPainter>

class IIslandClaimCallback;

class Island
{
	public:
		Island(const QPoint &position, int size, int item);

		QPoint position() const;

		int size() const;
		int score() const;
		int item() const;

		IIslandClaimCallback *claim(const QColor &color);

		void update(long delta);
		void draw(QPainter &painter, bool unclaimed);

		void lowerScore();

	private:
		IIslandClaimCallback *resolveItemCallback() const;

		QPoint m_position;
		QColor m_color;

		int m_size;
		int m_item;

		float m_ripple;

		bool m_claimed;
};

#endif // ISLAND_H
