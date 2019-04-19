#include "BounceOrbCannon.h"



BounceOrbCannon::BounceOrbCannon(Game* game) : Gun(game->getTexture("ArmBounceCannon"), game->getTexture("BounceBullet"), 5, 25, 1000, 5, 40, 200, &_effect, BounceOrbCannon_Weapon,game->getTexture("BounceCannonIcon"), false, BHBullet)
{
	_offset = { 24, -1 };
}


BounceOrbCannon::~BounceOrbCannon()
{
}
