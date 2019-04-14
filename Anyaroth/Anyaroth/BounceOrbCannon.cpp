#include "BounceOrbCannon.h"



BounceOrbCannon::BounceOrbCannon(Game* game) : Gun(game->getTexture("ArmPistol"), game->getTexture("Coin"), 30, 25, 1000, 5, 40, 200, &_effect, BounceOrbCannon_Weapon, false)
{
	_offset = { 24, -1 };
}


BounceOrbCannon::~BounceOrbCannon()
{
}
