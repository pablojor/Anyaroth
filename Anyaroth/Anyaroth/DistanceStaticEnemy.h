#pragma once

#include "Enemy.h"

class DistanceStaticEnemy : public Enemy
{
	private:
		Player* _player;

	public:
		DistanceStaticEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);

		virtual void update();
};
