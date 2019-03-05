#pragma once

#include "Enemy.h"
#include "MovingComponent.h"


class MartyrEnemy : public Enemy
{
	private:
		int _explosionRange = 40, _impulse = 20;
		int _canDie;

	public:
		MartyrEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);

		virtual void update();
};