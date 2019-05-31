#include "PlayerPlacementCallback.h"
#include "Player.h"

void PlayerPlacementCallback::invoke(Player *player)
{
	player->place();
}
