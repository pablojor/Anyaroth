#include "ImprovedRifle.h"

ImprovedRifle::ImprovedRifle(Game* game) : Gun(game, game->getTexture("ArmImprovedRifle"), game->getTexture("basicRifleShot"), "pistolShot", 100, 4, 1000, 36, 160, 100,  &_effect, ImprovedRifle_Weapon, game->getTexture("ImprovedRifleIcon"), true)
{
	_offset = { 24, -1 };
}


ImprovedRifle::~ImprovedRifle()
{
}
