#pragma once
#include "DistanceEnemy.h"

class DistanceStaticEnemy : public DistanceEnemy
{
public:
	DistanceStaticEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool);

	virtual void update(const double& deltaTime);
};