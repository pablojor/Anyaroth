#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "FollowingComponent.h"
#include "HurtRenderComponent.h"
#include "checkML.h"

class Gun;

class Arm : public GameObject
{
protected:
	GameObject* _owner = nullptr;
	TransformComponent* _transform = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;
	FollowingComponent* _followC = nullptr;
	//HurtRenderComponent* _hurt = nullptr;

public:
	Arm(Game* g, GameObject* owner, Vector2D offset = { 0,0 });
	virtual ~Arm() {};

	void setTexture(Texture* armTex);

	void lookAtTarget(const Vector2D& target) const;

	void hurt() const;
	void die() const;
};