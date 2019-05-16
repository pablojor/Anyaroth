#pragma once
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "Texture.h"

class GameObject;

class FollowingComponent : public PhysicsComponent
{
protected:
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;
	TransformComponent* _transformOther = nullptr;
	GameObject* _other = nullptr;
	Vector2D _offset;
	Vector2D _initialOffset;

public:
	FollowingComponent(GameObject* obj, GameObject* other);
	virtual ~FollowingComponent() {}

	virtual void update(double deltaTime);

	inline void setOffset(Vector2D offset) { _offset = offset; }
	inline Vector2D getOffset() const { return _offset; }

	inline void setInitialOffset(Vector2D offset) { _initialOffset = offset; _offset = offset; }
	inline Vector2D getInitialOffset() const { return _initialOffset; }

	inline GameObject* getOther() const { return _other; }
};