#include "GravityBombCannon.h"



GravityBombCannon::GravityBombCannon(Game* game) : Gun(game->getTexture("ArmBHCannon"), game->getTexture("BHBullet"), 45, 5, 150, 3, 30, 400,  &_effect, BHCannon_Weapon, game->getTexture("BHCannonIcon"), false, BHBullet)
{
	_offset = { 24, -1 };
	_animType = PlayerBHCannonArmType;
}


GravityBombCannon::~GravityBombCannon()
{
}
