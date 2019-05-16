#include "BounceOrbCannon.h"

BounceOrbCannon::BounceOrbCannon(Game* game) : Gun(game, game->getTexture("ArmBounceCannon"), game->getTexture("BounceBullet"), "orb", 50, 20, 1000, 5, 40, 200, &_effect, BounceOrbCannon_Weapon,game->getTexture("BounceCannonIcon"), false, BHBullet)
{
	_offset = { 24, -1 };
	_animType = PlayerBounceCannonArmType;
	createParticles = false;
}

BounceOrbCannon::~BounceOrbCannon() {}