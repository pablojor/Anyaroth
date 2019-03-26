#pragma once
#include "GameComponent.h"
#include "Bullet.h"

class PoolWrapper : public GameComponent
{
public:
	PoolWrapper(Game* game);
	virtual ~PoolWrapper();

	/****TEMPORAL****/
	virtual Bullet* getUnusedObject() { return nullptr; };
	virtual Bullet* addNewBullet() {return nullptr;};
};