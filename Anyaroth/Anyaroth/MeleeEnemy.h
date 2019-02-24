#pragma once

#include "Enemy.h"
#include "MovingComponent.h"


class MeleeEnemy : public Enemy
{
	public:
		MeleeEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);

		void noLongerAttacking() { _attacking = false; }
		virtual void update();
};