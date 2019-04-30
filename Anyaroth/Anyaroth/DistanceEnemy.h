#pragma once
#include "Enemy.h"
#include "EnemyArm.h"
#include "BulletPool.h"

class DistanceEnemy : virtual public Enemy
{
protected:
	EnemyArm* _arm;
	Gun* _myGun = nullptr;
	BulletPool* _myBulletPool = nullptr;

	bool _armVision = false;
	double _fail = 7.5;

public:
	DistanceEnemy(Game* g, Player* player, Vector2D pos, Texture* texture, BulletPool* pool, Vector2D offset = { 10, 12 });
	virtual ~DistanceEnemy() { delete _myGun; }

	inline bool ArmVision() const { return _armVision; }
	inline Gun* getGun() const { return _myGun; }

	virtual void update(const double& deltaTime);
	void raycast();
	void shoot();
};