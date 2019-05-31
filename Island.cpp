#include <cmath>

#include "Island.h"
#include "IslandScoreCallback.h"
#include "LowerScoreClaimCallback.h"
#include "ReverseDirectionClaimCallback.h"
#include "SlowTimeClaimCallback.h"
#include "SpawnIslandsClaimCallback.h"

Island::Island(const QPoint &position, int size, int item)
	: m_position(position)
	, m_size(size)
	, m_item(item)
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

int Island::item() const
{
	if (m_size > 15)
	{
		return m_item;
	}

	return -1;
}

IIslandClaimCallback *Island::claim(const QColor &color)
{
	m_claimed = true;
	m_color = color.dark();

	if (item() > -1)
	{
		return resolveItemCallback();
	}

	return new IslandScoreCallback(score());
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
	static QList<QImage> items =
	{
		QImage("resources/item-change-direction.png"),
		QImage("resources/item-lower-score.png"),
		QImage("resources/item-slow-time.png"),
		QImage("resources/item-spawn-islands.png")
	};

	if (unclaimed)
	{
		static const QFont font("sans", 10);

		const QRect rect(m_position - QPoint(m_size, m_size), QSize(m_size * 2, m_size * 2));

		painter.setFont(font);
		painter.setPen(QPen(QColor("#1cdc9a"), 2));
		painter.drawEllipse(m_position, m_size, m_size);

		const auto itemIndex = item();

		if (itemIndex > -1)
		{
			const auto itemImage = items[itemIndex];

			const auto ix = rect.x() + (rect.width() - itemImage.width()) / 2;
			const auto iy = rect.y() + (rect.height() - itemImage.height()) / 2;

			painter.drawImage(ix, iy, itemImage);
		}
		else
		{
			painter.drawText(rect, Qt::AlignCenter, QString::number(score()));
		}
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

void Island::lowerScore()
{
	m_size = 50;
}

IIslandClaimCallback *Island::resolveItemCallback() const
{
	switch (item())
	{
		case 0:
		{
			return new ReverseDirectionClaimCallback();
		}

		case 1:
		{
			return new LowerScoreClaimCallback();
		}

		case 2:
		{
			return new SlowTimeClaimCallback();
		}

		case 3:
		{
			return new SpawnIslandsClaimCallback();
		}
	}

	return nullptr;
}
