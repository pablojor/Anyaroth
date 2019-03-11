#pragma once
#include "Enemy.h"
#include "EnemyArm.h"

enum GunType;

class DistanceEnemy : public Enemy
{
protected:
	EnemyArm* _arm;
	bool _armVision = false;

public:
	DistanceEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, GunType type);
	virtual ~DistanceEnemy();

	inline bool ArmVision() const { return _armVision; }
	void RayCast();
};