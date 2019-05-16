#include "ImprovedRifle.h"

ImprovedRifle::ImprovedRifle(Game* game) : Gun(game, game->getTexture("ArmImprovedRifle"), game->getTexture("RifleBullet"), "rifle2", 100, 4, 1000, 40, 200, 100,  &_effect, ImprovedRifle_Weapon, game->getTexture("ImprovedRifleIcon"), true, RifleBullet)
{
	_offset = { 24, -1 };
	_animType = PlayerImprovedRifleArmType;
}

ImprovedRifle::~ImprovedRifle() {}