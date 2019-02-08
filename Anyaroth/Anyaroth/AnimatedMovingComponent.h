#pragma once
#include "MovingComponent.h"
#include "AnimatedSpriteComponent.h"

class AnimatedMovingComponent :
	public MovingComponent
{
protected:
	AnimatedSpriteComponent * _ac = nullptr;
public:
	AnimatedMovingComponent(TransformComponent* trans, double x, double y, AnimatedSpriteComponent * ac) : _ac(ac), MovingComponent( trans,  x,  y) {};
	virtual ~AnimatedMovingComponent() {};

	virtual void update();
};

