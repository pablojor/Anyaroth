#include "PlasmaSniper.h"



PlasmaSniper::PlasmaSniper(Game* game) : Gun(game->getTexture("ArmSniper"), game->getTexture("SniperBullet"), 100, 60, 1000, 1, 30, 1500, &_effect, PlasmaSniper_Weapon, game->getTexture("SniperIcon"), false, SniperBullet)
{
	_offset = { 24, -1 };
	_animType = PlayerSniperArmType;
}

PlasmaSniper::~PlasmaSniper()
{
}
