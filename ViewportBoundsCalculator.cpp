#include "ViewportBoundsCalculator.h"
#include "IPlayerProvider.h"

ViewportBoundsCalculator::ViewportBoundsCalculator(int index, IPlayerProvider &playerProvider)
	: m_index(index)
	, m_playerProvider(playerProvider)
{
}

QRect ViewportBoundsCalculator::calculate(const QPainter &painter) const
{
	const auto &viewport = painter.viewport();
	const auto &players = m_playerProvider.players();

	const auto width = viewport.width() / players.count();

	return { m_index * width, 0, width, viewport.height() };
}
