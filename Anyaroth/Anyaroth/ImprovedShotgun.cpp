#include "ImprovedShotgun.h"



ImprovedShotgun::ImprovedShotgun(Game * game) : Shotgun(game->getTexture("ArmShotgun"), game->getTexture("PistolBullet"), 100, 7/*da�o por bala*/, 60, 2, 50, 800, &_effect, ImprovedShotgun_Weapon, false)
{
	_angleBetweenBullet = 20;
	_numBulletsPerShot = 5;
}


ImprovedShotgun::~ImprovedShotgun()
{
}
