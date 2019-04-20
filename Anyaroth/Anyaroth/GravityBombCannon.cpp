#include "GravityBombCannon.h"



GravityBombCannon::GravityBombCannon(Game* game) : Gun(game, game->getTexture("ArmBHCannon"), game->getTexture("BHBullet"), "pistolShot", 45, 3, 150, 3, 30, 400,  &_effect, GravityBombCannon_Weapon, game->getTexture("BHCannonIcon"), false, Default)
{
	_offset = { 24, -1 };
}


GravityBombCannon::~GravityBombCannon()
{
}
