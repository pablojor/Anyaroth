#pragma once

#include "Enemy.h"
#include "MovingComponent.h"


class MartyrEnemy : public Enemy
{
	private:
		Player* _player;
		int _explosionRange = 40, _impulse = 5;

	public:
		MartyrEnemy(Player* player, Game* g, PlayState* play,Texture* texture, Vector2D posIni);

		void noLongerAttacking() { _attacking = false; }
		virtual void update();
};