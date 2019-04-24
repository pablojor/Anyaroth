#include "BasicShotgun.h"


BasicShotgun::BasicShotgun(Game * game) : Shotgun(game, game->getTexture("ArmShotgun"), game->getTexture("ShotgunBullet"), "shotgun1", 40, 4/*da�o por bala*/, 90, 3, 48, 800, &_effect, BasicShotgun_Weapon, game->getTexture("ShotgunIcon"), false, ShotGunBullet)
{
	_angleBetweenBullet = 30;
	_numBulletsPerShot = 2;
	_animType = PlayerShotgunArmType;
}

BasicShotgun::~BasicShotgun() {}
