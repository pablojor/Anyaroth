#pragma once
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Texture.h"

class GameComponent;

class FollowingComponent : public PhysicsComponent
{
protected:
	TransformComponent* _transform = nullptr;
	TransformComponent* _transformOther = nullptr;
	GameComponent* _other = nullptr;
	Vector2D _offset;
	Vector2D _initialOffset;

public:
	FollowingComponent(GameComponent* obj, GameComponent* other);
	virtual ~FollowingComponent() {}

	virtual void update();

	inline void setOffset(Vector2D offset) { _offset = offset; }
	inline Vector2D getOffset() const { return _offset; }

	inline void setInitialOffset(Vector2D offset) { _initialOffset = offset; _offset = offset; }
	inline Vector2D getInitialOffset() const { return _initialOffset; }

	inline GameComponent* getOther() const { return _other; }
};