#include "BasicRifle.h"



BasicRifle::BasicRifle(Game* game) : Gun(game->getTexture("ArmRifle"), game->getTexture("RifleBullet"), 100, 15, 1000, 30, 120, 170, &_effect, BasicRifle_Weapon, game->getTexture("RifleIcon"), true, RifleBullet)
{
	_offset = { 24, -1 };
	_animType = PlayerRifleArmType;
}


BasicRifle::~BasicRifle()
{
}
