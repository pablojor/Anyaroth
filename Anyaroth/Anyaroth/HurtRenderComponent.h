#pragma once

#include "PhysicsComponent.h"

class Texture;

class HurtRenderComponent : public PhysicsComponent
{
private:
	Texture* _texture = nullptr;

	double _hurtTime = 250;
	double _startTime = _hurtTime;
	bool _hurt = false;
public:
	HurtRenderComponent(GameComponent * obj);
	virtual ~HurtRenderComponent();

	virtual void update();

	void hurt();
	void die();
};

