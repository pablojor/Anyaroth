#include "PlasmaSniper.h"



PlasmaSniper::PlasmaSniper(Game* game) : Gun(game->getTexture("ArmShotgun"), game->getTexture("Coin"), 100, 60, 1000, 1, 30, 1500, &_effect, false, PlasmaSniper_Weapon)
{
	_offset = { 24, -1 };
}

PlasmaSniper::~PlasmaSniper()
{
}
