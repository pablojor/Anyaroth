#include "PlasmaSniper.h"



PlasmaSniper::PlasmaSniper(Game* game) : Gun(game, game->getTexture("ArmSniper"), game->getTexture("SniperBullet"), "plasmaSniper", 100, 25, 1000, 1, 30, 1500, &_effect, PlasmaSniper_Weapon, game->getTexture("SniperIcon"), false, SniperBullet)
{
	_offset = { 24, -1 };
	_animType = PlayerSniperArmType;
}

PlasmaSniper::~PlasmaSniper()
{
}
