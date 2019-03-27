#pragma once
#include "Enemy.h"
#include "EnemyArm.h"

enum GunType;

class BulletPool;

class DistanceEnemy : public Enemy
{
protected:
	EnemyArm* _arm;
	bool _armVision = false;
	Gun* _myGun = nullptr;
	BulletPool* _myBulletPool = nullptr;
	double _fail = 7.5;

public:
	DistanceEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool);
	virtual ~DistanceEnemy() { delete _myGun; }

	inline bool ArmVision() const { return _armVision; }

	void RayCast();

	Gun* getGun() { return _myGun; }

	virtual void update(const double& deltaTime);
};