#pragma once

#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Texture.h"

class GameComponent;

class FollowingComponent : public PhysicsComponent
{
protected:
	TransformComponent* _transform;
	TransformComponent* _transformOther;
	Vector2D _offset;
public:
	FollowingComponent(GameComponent* obj, GameComponent* other);
	virtual ~FollowingComponent();

	virtual void update();
};

