#pragma once
#include "Boss.h"
#include "LaserHandler.h"

class Boss2 :
	public Boss
{
private:
	bool _jump = false;
	LaserHandler* _lasers = nullptr;
public:
	Boss2(Game* g, Player* player, Vector2D pos, BulletPool* pool);
	~Boss2();
	void Jump();

	virtual void beginCollision(GameObject* other, b2Contact* contact);

	virtual void fase1(const double& deltaTime);
	virtual void beetwenFases(const double& deltaTime);

};

