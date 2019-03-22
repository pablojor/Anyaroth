#include "BounceOrbCannon.h"



BounceOrbCannon::BounceOrbCannon(Game* game) : Gun(game->getTexture("ArmPistol"), game->getTexture("PistolBullet"), 100, 15, 1000, 30, 120, 200, false, Bouncing)
{
	_offset = { 24, -1 };
}


BounceOrbCannon::~BounceOrbCannon()
{
}
