#pragma once
#include "GameComponent.h"

class PoolWrapper : public GameComponent
{
public:
	PoolWrapper(Game* game);
	virtual ~PoolWrapper();
};