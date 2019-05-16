#include "ImprovedShotgun.h"

ImprovedShotgun::ImprovedShotgun(Game * game) : Shotgun(game, game->getTexture("ArmImprovedShotgun"), game->getTexture("ShotgunBullet"), "shotgun2", 50, 5, 100, 4, 80, 700, &_effect, ImprovedShotgun_Weapon,game->getTexture("ImprovedShotgunIcon"), false)
{
	_angleBetweenBullet = 10;
	_numBulletsPerShot = 4;
	_animType = PlayerImprovedShotgunArmType;
}

ImprovedShotgun::~ImprovedShotgun() {}