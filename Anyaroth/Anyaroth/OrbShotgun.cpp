#include "OrbShotgun.h"

OrbShotgun::OrbShotgun(Game* g) : Shotgun(g, g->getTexture("AngraArmBounceCannon"), g->getTexture("BounceBullet"), "orb", 10, 5, 1000, 10, 50, 100, &_effect, BossOrbCanon_Weapon, nullptr, false)
{
	_numBulletsPerShot = 4;
	_angleBetweenBullet = 10;
}

OrbShotgun::~OrbShotgun() {}