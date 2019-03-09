#include "BasicShotgun.h"



BasicShotgun::BasicShotgun(Game * game) : Gun(game->getTexture("ArmShotgun"), 2, 30)
{

}

BasicShotgun::~BasicShotgun()
{
}

void BasicShotgun::shoot()
{
	//TEMPORAL
	Gun::shoot();
}
