#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"
#include "LaserContainer.h"

class LaserHandler : public GameObject
{
private:
	int _numLasers;
	bool _active = false;
	vector<LaserContainer*> _lasers;

	int timeToshot = 0, timeBetweenShot = 3000, timeToEnd = 3000;

	bool isShooting = false, shootStareted = false;

public:
	LaserHandler(Game* g, Texture* container, Texture* laser, Player* player, int numLasers);
	virtual ~LaserHandler() {}

	virtual void update(const double& deltaTime);

	void Shoot();
	void Stop();
	void Activate() { _active = true; }
};
