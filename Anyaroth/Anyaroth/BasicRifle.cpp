#include "BasicRifle.h"

BasicRifle::BasicRifle(Game* game) : Gun(game, game->getTexture("ArmRifle"), game->getTexture("RifleBullet"), "rifle1", 100, 3, 1000, 30, 150, 150, &_effect, BasicRifle_Weapon, game->getTexture("RifleIcon"), true, RifleBullet)
{
	_offset = { 24, -1 };
	_animType = PlayerRifleArmType;
}

BasicRifle::~BasicRifle() {}