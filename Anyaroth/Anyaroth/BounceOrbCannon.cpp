#include "BounceOrbCannon.h"



BounceOrbCannon::BounceOrbCannon(Game* game) : Gun(game->getTexture("ArmPistol"), game->getTexture("Coin"), 30, 15, 1000, 30, 120, 200, false, BounceOrbCannon_Weapon)
{
	_offset = { 24, -1 };
}


BounceOrbCannon::~BounceOrbCannon()
{
}
