#pragma once
#include "BulletEffect.h"
class GravityBulletEffect :
	public BulletEffect
{
private:
	int _maxAbsorbingTime = 150;
public:
	GravityBulletEffect(int maxAbsorbTime);
	virtual ~GravityBulletEffect();

	virtual void beginCollision(Bullet* bullet, GameObject* other, b2Contact* contact);
	virtual void update(Bullet* bullet, double time);
	virtual void reset(Bullet* bullet);
	virtual void init(Bullet* bullet);
	void stop(Bullet* bullet);
};

