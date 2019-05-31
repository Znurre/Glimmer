#ifndef ISLANDSCORECALLBACK_H
#define ISLANDSCORECALLBACK_H

#include "IIslandClaimCallback.h"

class IslandScoreCallback : public IIslandClaimCallback
{
	public:
		IslandScoreCallback(int score);

		void invoke(Player *player, IPlayerProvider &playerProvider, World &world) override;

	private:
		int m_score;
};

#endif // ISLANDSCORECALLBACK_H
