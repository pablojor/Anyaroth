#include "ShooterInterface.h"



ShooterInterface::ShooterInterface()
{
}


ShooterInterface::~ShooterInterface()
{
}


void ShooterInterface::init(GameComponent* shootingObject, PoolWrapper* bPool)
{
	_shootingObject = shootingObject;
	_bPool = bPool;
}