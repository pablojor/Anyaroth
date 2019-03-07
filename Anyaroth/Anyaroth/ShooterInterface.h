#pragma once
#include "GameComponent.h"
#include "PoolWrapper.h"

class ShooterInterface
{
protected:
	GameComponent* _shootingObject = nullptr; //El objeto que dispara las balas (/!\ NO ES EL GUN, SERÁ ARM O ENEMY NORMALMENTE)
	PoolWrapper* _bPool = nullptr; //La pool de balas empleada

public:
	ShooterInterface() {}
	virtual ~ShooterInterface() {}

	virtual void init(GameComponent* shootingObject, PoolWrapper* bPool);
	virtual void shoot(Vector2D bulletPosition, Vector2D bulletDir, double angle) = 0;
};