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

	bool isShooting = false, shootStareted = false, _isWarning = false;

public:
	LaserHandler(Game* g, Texture* container, Texture* laser, Player* player, int numLasers, int span, Vector2D pos);
	virtual ~LaserHandler() {}

	virtual void update(double deltaTime);

	void Shoot();
	void Stop();
	void Activate() { _active = true; }
	void Deactivate() { Stop(); _active = false; }
};
