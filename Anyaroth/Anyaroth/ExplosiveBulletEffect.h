#pragma once
#include "BulletEffect.h"

class ExplosiveBulletEffect : public BulletEffect
{
private:
	int _explodeTime = 100;

public:
	ExplosiveBulletEffect(int explodeTime);
	~ExplosiveBulletEffect();

	virtual void beginCollision(Bullet* bullet, GameComponent* other, b2Contact* contact);
	virtual void update(Bullet* bullet, double time);
	virtual void init(Bullet* bullet);
	void explosion(Bullet* bullet);
};