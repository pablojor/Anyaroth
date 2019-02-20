#pragma once
#include "GameComponent.h"
#include "PoolWrapper.h"


////////////////////////////////////////////////////////////////
//		La clase Shooter implementa el método de disparo 
//		básico de las armas shoot().
//		Para hacer un nuevo tipo de disparo, hay que crear
//		una nueva clase que herede de Shooter y redefina
//		el método shoot().
////////////////////////////////////////////////////////////////

class Shooter
{
private:
	GameComponent* _shootingObject = nullptr; //El objeto que dispara las balas (/!\ NO ES EL GUN, SERÁ ARM o ENEMY NORMALMENTE)
	PoolWrapper* _bPool = nullptr; //La pool de balas empleada
public:
	Shooter();
	virtual ~Shooter();
	
	virtual void init(GameComponent* shootingObject, PoolWrapper* bPool);
	virtual void shoot();
};

