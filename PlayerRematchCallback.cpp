#include "PlayerRematchCallback.h"
#include "Player.h"

void PlayerRematchCallback::invoke(Player *player)
{
	player->rematch();
}
