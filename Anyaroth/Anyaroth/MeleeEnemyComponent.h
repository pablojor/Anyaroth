#pragma once

#include "Enemy.h"
#include "MovingComponent.h"


class MeleeEnemyComponent : public Enemy
{
	public:
		MeleeEnemyComponent(Game* g, Player* player, Texture* texture, Vector2D posIni);

		void noLongerAttacking() { _attacking = false; }
		virtual void update();
};