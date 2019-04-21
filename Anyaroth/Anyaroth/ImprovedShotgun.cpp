#include "ImprovedShotgun.h"



ImprovedShotgun::ImprovedShotgun(Game * game) : Shotgun(game, game->getTexture("ArmImprovedShotgun"), game->getTexture("ShotgunBullet"), "improvedShotgunShot", 50, 4/*da�o por bala*/, 100, 2, 50, 800, &_effect, ImprovedShotgun_Weapon,game->getTexture("ImprovedShotgunIcon"), false)
{
	_angleBetweenBullet = 10;
	_numBulletsPerShot = 4;
	_animType = PlayerImprovedShotgunArmType;
}


ImprovedShotgun::~ImprovedShotgun()
{
}
