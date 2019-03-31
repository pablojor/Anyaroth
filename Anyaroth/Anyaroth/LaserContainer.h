#pragma once
#include "GameObject.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "Laser.h"

class LaserContainer : public GameObject
{
private:
	Vector2D _pos;
	Laser* _laser;

public:
	LaserContainer(Game* g, Vector2D pos, Texture* container, Texture* laser, Player* player);
	virtual ~LaserContainer() {}

	virtual void update(const double& deltaTime) {}

	void Shoot(double angle) { _laser->Shoot(angle); }
	void Stop() { _laser->Stop(); }
};