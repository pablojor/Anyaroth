#include "BasicPistol.h"


BasicPistol::BasicPistol(Game* game) : Gun(game->getTexture("ArmPistol"), game->getTexture("PistolBullet"), 100, 10, 1000, 12, 60, 270, false, Pistol_Weapon)
{
	_offset = { 24, -1 };
}

BasicPistol::~BasicPistol() {}