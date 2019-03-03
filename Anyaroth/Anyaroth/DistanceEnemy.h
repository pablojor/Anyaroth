#pragma once
#include "Enemy.h"
#include "EnemyArm.h"

class DistanceEnemy : public Enemy
{
	protected:
		EnemyArm* _arm;
		bool _armVision = false;
	public:
		DistanceEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag);
		virtual ~DistanceEnemy() {};

		inline bool ArmVision() const { return _armVision; }
		void RayCast();
};

