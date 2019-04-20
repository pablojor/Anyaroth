#include "BomberGun.h"



BomberGun::BomberGun(Game* game) : Gun(game, game->getTexture("ArmShotgun"), game->getTexture("Coin"), "pistolShot", 0, 10, 600, 3, 30, 400, &_effect, BomberGun_Weapon, false)
{
}


BomberGun::~BomberGun()
{
}
