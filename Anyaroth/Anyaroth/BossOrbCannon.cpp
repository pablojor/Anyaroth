#include "BossOrbCannon.h"

BossOrbCannon::BossOrbCannon(Game* game) : Gun(game, game->getTexture("ArmPistol"), game->getTexture("Coin"), "orb", 20, 25, 1000, 5, 40, 200, &_effect, BossOrbCanon_Weapon, false)
{
	_offset = { 24, -1 };
}

BossOrbCannon::~BossOrbCannon() {}