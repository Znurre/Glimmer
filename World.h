#ifndef WORLD_H
#define WORLD_H

#include <cmath>

#include <QPoint>
#include <QVector>
#include <QPainter>
#include <QSet>

class Island
{
	public:
		Island() = default;

		Island(const QPoint &position, int size)
			: m_position(position)
			, m_size(size)
			, m_ripple(0)
			, m_claimed(false)
		{
		}

		QPoint position() const
		{
			return m_position;
		}

		int size() const
		{
			return m_size;
		}

		int score() const
		{
			return round((40 - m_size) / 10.0f);
		}

		int claim(const QColor &color)
		{
			m_claimed = true;
			m_color = color.dark();

			return score();
		}

		void update(long delta)
		{
			if (m_ripple > 10)
			{
				return;
			}

			if (m_claimed)
			{
				m_ripple += delta / 20.0f;
			}
		}

		void draw(QPainter &painter, bool unclaimed)
		{
			const QRect rect(m_position - QPoint(m_size, m_size), QSize(m_size * 2, m_size * 2));

			if (unclaimed)
			{
				painter.setPen(QPen(Qt::green, 2));
				painter.drawEllipse(m_position, m_size, m_size);
				painter.drawText(rect, Qt::AlignCenter, QString::number(score()));
			}
			else
			{
				painter.setPen(QPen(m_color, 2));
				painter.drawEllipse(m_position, m_size, m_size);
			}

			if (m_ripple > 0)
			{
				painter.setOpacity(1.0f - (m_ripple / 10.0f));
				painter.setPen(QPen(m_color.light(400), 2));
				painter.drawEllipse(m_position, (int)(m_size + m_ripple), (int)(m_size + m_ripple));
				painter.setOpacity(1.0f);
			}
		}

	private:
		QPoint m_position;
		QColor m_color;

		int m_size;

		float m_ripple;

		bool m_claimed;
};

class World
{
	public:
		World();

		float createIsland(const QPoint &origin, float offset);

		void update(long delta);
		void draw(QPainter &painter);
		void reset();

		int tryClaimIsland(const QPoint &point, const QColor &color);

	private:
		QSet<Island *> m_unclaimedIslands;
		QVector<Island *> m_islands;
};

#endif // WORLD_H
