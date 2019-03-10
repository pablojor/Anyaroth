#pragma once
#include "DistanceEnemy.h"

class DistanceDynamicEnemy : public DistanceEnemy
{
public:
	DistanceDynamicEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
	virtual void update(double time);
};