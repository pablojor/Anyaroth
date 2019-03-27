#pragma once
#include "Bullet.h"
class GravityBullet :
	public Bullet
{
private:
	bool _absorbing = false;
	int _absorbingTime = 0;
	int _maxAbsorbingTime = 150;
public:
	GravityBullet(Game* game);
	virtual ~GravityBullet();

	virtual void beginCollision(GameComponent* other, b2Contact* contact);
	virtual void update(double time);
	virtual void reset();
	void stop();
	virtual void init(Texture* texture, const Vector2D& position, const double& speed, const double& damage, const double& angle, const double& range, const string& tag);
};

