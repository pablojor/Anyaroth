#include "BasicPistol.h"

BasicPistol::BasicPistol(Game* game) : Gun(game, game->getTexture("ArmPistol"), game->getTexture("PistolBullet"), "pistolShot", 100, 3, 1000, 12, 84, 250, &_effect, Pistol_Weapon, game->getTexture("PistolIcon"), false, Default)
{
	_offset = { 24, -1 };
	_animType = PlayerPistolArmType;
}

BasicPistol::~BasicPistol() {}