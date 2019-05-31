#include "IslandScoreCallback.h"
#include "Player.h"

IslandScoreCallback::IslandScoreCallback(int score)
	: m_score(score)
{
}

void IslandScoreCallback::invoke(Player *player, IPlayerProvider &playerProvider, World &world)
{
	Q_UNUSED(playerProvider)
	Q_UNUSED(world)

	player->addScore(m_score * (player->combo() + 1));
}
