#pragma once
#include "Enemy.h"

class DistanceDynamicEnemy : public Enemy
{
	public:
		DistanceDynamicEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);

		virtual void update();
};

