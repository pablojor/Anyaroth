#pragma once
#include "PhysicsComponent.h"

class Texture;

class HurtRenderComponent : public PhysicsComponent
{
private:
	Texture* _texture = nullptr;
	double _hurtTime = 250, _startTime, _timer;
	bool _hurt = false;

public:
	HurtRenderComponent(GameComponent * obj);
	virtual ~HurtRenderComponent() {}

	virtual void update(double time);

	void hurt();
	void die();
};