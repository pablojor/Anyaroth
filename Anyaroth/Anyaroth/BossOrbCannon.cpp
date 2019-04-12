#include "BossOrbCannon.h"



BossOrbCannon::BossOrbCannon(Game* game) : Gun(game->getTexture("ArmPistol"), game->getTexture("Coin"), 20, 25, 1000, 5, 40, 200, &_effect, false, BossOrbCanon_Weapon)
{
	_offset = { 24, -1 };
}


BossOrbCannon::~BossOrbCannon()
{
}
