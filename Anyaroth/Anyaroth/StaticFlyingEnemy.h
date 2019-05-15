#pragma once
#include "DistanceStaticEnemy.h"

class StaticFlyingEnemy : public DistanceStaticEnemy
{
public:
	StaticFlyingEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool);
	virtual ~StaticFlyingEnemy() {}
};