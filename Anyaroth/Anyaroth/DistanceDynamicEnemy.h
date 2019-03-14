#pragma once
#include "DistanceEnemy.h"


class DistanceDynamicEnemy : public DistanceEnemy
{
public:
	DistanceDynamicEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool);
	virtual void update(double time);
};