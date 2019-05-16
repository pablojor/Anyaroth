#pragma once
#include "DistanceEnemy.h"

class DistanceStaticEnemy : public DistanceEnemy
{
public:
	DistanceStaticEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool = nullptr);

	virtual void update(double deltaTime);
	virtual void die();
};