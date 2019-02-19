#pragma once

#include "Enemy.h"
#include "MovingComponent.h"


class MeleeEnemy : public Enemy
{
	public:
		MeleeEnemy(Player* player, Game* g, Texture* texture, Vector2D posIni);
		~MeleeEnemy() {};

		void noLongerAttacking() { _attacking = false; }
		virtual void update();
};