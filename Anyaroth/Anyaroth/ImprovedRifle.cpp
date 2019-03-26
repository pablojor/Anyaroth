#include "ImprovedRifle.h"



ImprovedRifle::ImprovedRifle(Game* game) : Gun(game->getTexture("ArmPistol"), game->getTexture("PistolBullet"), 100, 20, 1000, 36, 160, 100, true)
{
	_offset = { 24, -1 };
}


ImprovedRifle::~ImprovedRifle()
{
}
