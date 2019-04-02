#pragma once
#include "Bullet.h"

class BouncingBullet : public Bullet
{
private:
	int _numBounces = 0;
	int _maxBounces = 4;
	double _bounceAngle = 90;
	bool _bounce = false;
	bool _managingCollision = false;
	bool _isColliding = false;

public:
	BouncingBullet(Game* game);
	virtual ~BouncingBullet();

	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void endCollision(GameObject * other, b2Contact* contact);
	virtual void update(double time);
	virtual void reset();
	virtual void init(Texture* texture, const Vector2D& position, const double& speed, const double& damage, const double& angle, const double& range, const string& tag, string type = "");
};