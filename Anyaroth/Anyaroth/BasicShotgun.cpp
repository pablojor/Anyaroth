#include "BasicShotgun.h"


BasicShotgun::BasicShotgun(Game * game) : Shotgun(game->getTexture("ArmShotgun"), game->getTexture("ShotgunBullet"), 40, 500/*da�o por bala*/, 90, 3, 48, 800, &_effect)
{
	_angleBetweenBullet = 15;
	_numBulletsPerShot = 3;
}

BasicShotgun::~BasicShotgun() {}
