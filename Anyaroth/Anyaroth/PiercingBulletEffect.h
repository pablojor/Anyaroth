#pragma once
#include "BulletEffect.h"
class PiercingBulletEffect :
	public BulletEffect
{
private:
	bool _destroy = false; //true si colisiona con suelo
public:
	PiercingBulletEffect();
	virtual ~PiercingBulletEffect();

	virtual void beginCollision(Bullet* bullet, GameObject* other, b2Contact* contact);
	virtual void update(Bullet* bullet, double time);
	virtual void init(Bullet* bullet);
};

