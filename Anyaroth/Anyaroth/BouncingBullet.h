#pragma once
#include "Bullet.h"
class BouncingBullet :
	public Bullet
{
private:
	int _bounces = 0;
	int _maxBounces = 3;
	double _bounceAngle = 30;

public:
	BouncingBullet(Game* game);
	virtual ~BouncingBullet();

	virtual void beginCollision(GameComponent* other, b2Contact* contact);
	virtual void update(double time);
	virtual void reset();
};

