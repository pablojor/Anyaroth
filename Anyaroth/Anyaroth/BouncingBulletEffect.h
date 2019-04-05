#pragma once
#include "BulletEffect.h"
class BouncingBulletEffect :
	public BulletEffect
{
private:
	int _maxBounces = 4;

public:
	BouncingBulletEffect(int maxBounces);
	virtual ~BouncingBulletEffect();

	virtual void beginCollision(Bullet* bullet, GameObject* other, b2Contact* contact);
	virtual void endCollision(Bullet* bullet, GameObject * other, b2Contact* contact);
	virtual void update(Bullet* bullet, double time);
	virtual void reset(Bullet* bullet);
	virtual void init(Bullet* bullet);
};

