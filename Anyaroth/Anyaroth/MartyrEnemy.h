#pragma once

#include "Enemy.h"
#include "MovingComponent.h"


class MartyrEnemy : public Enemy
{
	public:
		MartyrEnemy(Player* player, Game* g, PlayState* play,Texture* texture, Vector2D posIni);

		void noLongerAttacking() { _attacking = false; }
		virtual void update();
};