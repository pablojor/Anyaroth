#pragma once
#include "Bullet.h"

class ExplosiveBullet : public Bullet
{
private:
	bool _explode = false;
	double _time = 0, _explodeTime = 100;

public:
	ExplosiveBullet(Game* game);
	~ExplosiveBullet();

	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void update(const double& deltaTime);
	void explosion();
};