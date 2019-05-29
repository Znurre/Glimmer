#ifndef VIEWPORTBOUNDSCALCULATOR_H
#define VIEWPORTBOUNDSCALCULATOR_H

#include <QPainter>

class IPlayerProvider;

class ViewportBoundsCalculator
{
	public:
		ViewportBoundsCalculator(int index, IPlayerProvider &playerProvider);

		QRect calculate(const QPainter &painter) const;

	private:
		int m_index;

		IPlayerProvider &m_playerProvider;
};

#endif // VIEWPORTBOUNDSCALCULATOR_H
