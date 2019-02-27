#pragma once

#include "Enemy.h"
#include "MovingComponent.h"

class MeleeEnemy : public Enemy
{
	private:
		bool _attackingR = false;
		bool _attackingL = false;
	public:
		MeleeEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
		virtual ~MeleeEnemy() { }
		virtual void update();
};