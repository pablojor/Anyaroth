#pragma once
#include "GameObject.h"

class Bullet;

class EffectInterface
{

	/*******************************************************************************/
	//	Las clases que heredan de EffectInterface implementan
	//	la funcionalidad de las balas (qué pasa cuándo colisionan, efectos, etc)
	/******************************************************************************/
public:
	EffectInterface();
	virtual ~EffectInterface();

	virtual void beginCollision(Bullet* bullet, GameObject* other, b2Contact* contact) = 0;
	virtual void update(Bullet* bullet, double time) = 0;
	virtual void reset(Bullet* bullet) = 0;
	virtual void endCollision(Bullet* bullet, GameObject* other, b2Contact* contact) {}
	virtual void init(Bullet* bullet) {}
};

