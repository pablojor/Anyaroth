#pragma once
#include "DistanceEnemy.h"

class DistanceStaticEnemy : public DistanceEnemy
{
public:
	DistanceStaticEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool);

	virtual void update(const double& deltaTime);
};