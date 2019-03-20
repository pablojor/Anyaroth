#pragma once
#include "DistanceEnemy.h"
class Boss1 : public DistanceEnemy
{
public:
	Boss1(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool);
	virtual ~Boss1() {};
};

