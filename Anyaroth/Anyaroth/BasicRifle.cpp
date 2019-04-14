#include "BasicRifle.h"



BasicRifle::BasicRifle(Game* game) : Gun(game->getTexture("ArmRifle"), game->getTexture("RifleBullet"), 100, 15, 1000, 30, 120, 170, &_effect, BasicRifle_Weapon, true, RifleBullet, game->getTexture("RifleIcon"))
{
	_offset = { 24, -1 };
}


BasicRifle::~BasicRifle()
{
}
