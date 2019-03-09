#pragma once
#include "DistanceEnemy.h"

class DistanceStaticEnemy : public DistanceEnemy
{
	private:

	public:
		DistanceStaticEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, GunType type);

		virtual void update();
};
