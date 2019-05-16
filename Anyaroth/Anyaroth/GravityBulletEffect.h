#pragma once
#include "BulletEffect.h"
#include "GravityBombDebuff.h"
#include <vector>

class GravityBulletEffect : public BulletEffect
{
private:
	int _maxAbsorbingTime = 150;
	int _absorbingRange = 20;
	string _auxTag = "Bullet";
	vector<GravityBombDebuff*> _debuffs;

public:
	GravityBulletEffect(int maxAbsorbTime);
	virtual ~GravityBulletEffect();

	virtual void beginCollision(Bullet* bullet, GameObject* other, b2Contact* contact);
	virtual void update(Bullet* bullet, double time);
	virtual void reset(Bullet* bullet);
	virtual void init(Bullet* bullet);
	void startAbsorbing(Bullet* bullet);
};