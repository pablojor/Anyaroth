#include "GravityBombCannon.h"



GravityBombCannon::GravityBombCannon(Game* game) : Gun(game->getTexture("ArmShotgun"), game->getTexture("Coin"), 45, 5, 150, 3, 30, 400,  &_effect, false, Default, game->getTexture("bHCannonIcon"))
{
	_offset = { 24, -1 };
}


GravityBombCannon::~GravityBombCannon()
{
}
