#include "ImprovedShotgun.h"



ImprovedShotgun::ImprovedShotgun(Game * game) : Shotgun(game->getTexture("ArmImprovedShotgun"), game->getTexture("ShotgunBullet"), 100, 4/*da�o por bala*/, 60, 2, 50, 800, &_effect, ImprovedShotgun_Weapon,game->getTexture("ImprovedShotgunIcon"), false)
{
	_angleBetweenBullet = 10;
	_numBulletsPerShot = 4;
}


ImprovedShotgun::~ImprovedShotgun()
{
}
