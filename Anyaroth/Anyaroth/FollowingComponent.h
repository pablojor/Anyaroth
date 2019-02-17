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
	Vector2D _initialOffset;
	GameComponent* _other;
public:
	FollowingComponent(GameComponent* obj, GameComponent* other);
	virtual ~FollowingComponent();

	virtual void update();

	void setOffset(Vector2D offset) { _offset = offset; }
	void setInitialOffset(Vector2D offset) { _initialOffset = offset; _offset = offset; }
	Vector2D getInitialOffset() { return _initialOffset; }

	GameComponent* getOther() { return _other; };
};

