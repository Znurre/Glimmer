#include <cmath>

#include "Island.h"

Island::Island(const QPoint &position, int size)
	: m_position(position)
	, m_size(size)
	, m_ripple(0)
	, m_claimed(false)
{
}

QPoint Island::position() const
{
	return m_position;
}

int Island::size() const
{
	return m_size;
}

int Island::score() const
{
	return round((40 - m_size) / 10.0f);
}

int Island::claim(const QColor &color)
{
	m_claimed = true;
	m_color = color.dark();

	return score();
}

void Island::update(long delta)
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

void Island::draw(QPainter &painter, bool unclaimed)
{
	if (unclaimed)
	{
		static const QFont font("sans", 10);

		const QRect rect(m_position - QPoint(m_size, m_size), QSize(m_size * 2, m_size * 2));

		painter.setFont(font);
		painter.setPen(QPen(QColor("#1cdc9a"), 2));
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
		painter.setPen(QPen(Qt::white, 2));
		painter.drawEllipse(m_position, (int)(m_size + m_ripple), (int)(m_size + m_ripple));
		painter.setOpacity(1.0f);
	}
}
