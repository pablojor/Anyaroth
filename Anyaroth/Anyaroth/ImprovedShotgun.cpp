#include "ImprovedShotgun.h"



ImprovedShotgun::ImprovedShotgun(Game * game) : Shotgun(game->getTexture("ArmShotgun"), game->getTexture("PistolBullet"), 100, 7/*daño por bala*/, 60, 2, 50, 800, false, ImprovedShotgun_Weapon)
{
	_angleBetweenBullet = 20;
	_numBulletsPerShot = 5;
}


ImprovedShotgun::~ImprovedShotgun()
{
}
