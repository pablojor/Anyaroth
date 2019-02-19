#pragma once

#include "Enemy.h"
#include "MovingComponent.h"


class MeleeEnemyComponent : public Enemy
{
	public:
		MeleeEnemyComponent(Game* g, Texture* texture, Vector2D posIni, Player* player);

		void noLongerAttacking() { _attacking = false; }
		virtual void update();
};