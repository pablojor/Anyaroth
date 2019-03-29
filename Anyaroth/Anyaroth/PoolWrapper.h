#pragma once
#include "GameObject.h"
#include "Bullet.h"

class PoolWrapper : public GameObject
{
public:
	PoolWrapper(Game* game);
	virtual ~PoolWrapper();

	/****TEMPORAL****/
	virtual Bullet* getUnusedObject() { return nullptr; };
	virtual Bullet* addNewBullet() {return nullptr;};
};