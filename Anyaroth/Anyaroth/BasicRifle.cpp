#include "BasicRifle.h"



BasicRifle::BasicRifle(Game* game) : Gun(game->getTexture("ArmPistol"), game->getTexture("PistolBullet"), 100, 15, 1000, 30, 120, 170, &_effect, true)
{
	_offset = { 24, -1 };
}


BasicRifle::~BasicRifle()
{
}
