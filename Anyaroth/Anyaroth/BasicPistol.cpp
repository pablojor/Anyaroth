#include "BasicPistol.h"

BasicPistol::BasicPistol(Game* game) : Gun(game->getTexture("ArmPistol"), game->getTexture("PistolBullet"), 100, 2, 1000, 12, 60, 270, &_effect, Pistol_Weapon, game->getTexture("PistolIcon"), false, Default)
{
	_offset = { 24, -1 };
}

BasicPistol::~BasicPistol() {}