#include "BasicShotgun.h"


BasicShotgun::BasicShotgun(Game * game) : Shotgun(game->getTexture("ArmShotgun"), game->getTexture("PistolBullet"), 100, 7/*da�o por bala*/, 60, 3, 48, 800, &_effect)
{
	_angleBetweenBullet = 30;
	_numBulletsPerShot = 3;
}

BasicShotgun::~BasicShotgun() {}
