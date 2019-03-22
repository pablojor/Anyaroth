#pragma once
#include "GameObject.h"

class PoolWrapper : public GameObject
{
public:
	PoolWrapper(Game* game);
	virtual ~PoolWrapper();
};