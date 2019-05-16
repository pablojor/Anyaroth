#include "BasicShotgun.h"

BasicShotgun::BasicShotgun(Game * game) : Shotgun(game, game->getTexture("ArmShotgun"), game->getTexture("ShotgunBullet"), "shotgun1", 30, 5, 100, 2, 60, 800, &_effect, BasicShotgun_Weapon, game->getTexture("ShotgunIcon"), false, ShotGunBullet)
{
	_angleBetweenBullet = 12;
	_numBulletsPerShot = 2;
	_animType = PlayerShotgunArmType;
}

BasicShotgun::~BasicShotgun() {}