#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "CustomAnimatedSpriteComponent.h"
#include "FollowingComponent.h"
#include "GunType_def.h"

class Gun;

class Arm : public GameObject
{
protected:
	GameObject* _owner = nullptr;
	TransformComponent* _transform = nullptr;
	CustomAnimatedSpriteComponent* _anim = nullptr;
	FollowingComponent* _followC = nullptr;

public:
	Arm(Game* g, GameObject* owner, Vector2D offset = { 0,0 });
	virtual ~Arm() {};

	void setTexture(Texture* armTex);
	void setAnimations(ArmAnimType type);
	void setOffSet(Vector2D newOff) { _followC->setInitialOffset(newOff); }

	void lookAtTarget(const Vector2D& target) const;

	void hurt() const;
	void die() const;
};