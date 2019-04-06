#pragma once
#include "EffectInterface.h"


class BulletEffect : public EffectInterface 
{
public:
	BulletEffect();
	virtual ~BulletEffect();

	virtual void beginCollision(Bullet* bullet, GameObject* other, b2Contact* contact);
	virtual void update(Bullet* bullet, double time);
	virtual void reset(Bullet* bullet);
};

