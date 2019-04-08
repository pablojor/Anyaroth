#include "GravityBombCannon.h"



GravityBombCannon::GravityBombCannon(Game* game) : Gun(game->getTexture("ArmBHCannon"), game->getTexture("BHBullet"), 45, 5, 150, 3, 30, 400,  &_effect, false, Default, game->getTexture("BHCannonIcon"))
{
	_offset = { 24, -1 };
}


GravityBombCannon::~GravityBombCannon()
{
}
