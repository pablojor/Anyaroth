#include "ShooterInterface.h"

void ShooterInterface::init(GameComponent* shootingObject, PoolWrapper* bPool)
{
	_shootingObject = shootingObject;
	_bPool = bPool;
}