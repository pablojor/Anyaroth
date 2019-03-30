#pragma once
#include "GameObject.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"

class LaserContainer : public GameObject
{
private:
	Vector2D _pos;

public:
	LaserContainer(Game* g, Vector2D pos, Texture* texture);
	virtual ~LaserContainer() {}

	virtual void update(const double& deltaTime) {}
};