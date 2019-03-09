#pragma once
#include "GameComponent.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"

class Gun;

class Arm : public GameComponent
{
protected:
	GameComponent* _owner = nullptr;
	TransformComponent* _transform = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;
	FollowingComponent* _followC = nullptr;
	Gun* _currentGun = nullptr;

public:
	Arm(Game* g, GameComponent* owner, Vector2D offset = { 0,0 });
	virtual ~Arm() {};

	void setTexture(Texture* armTex);

	void lookAtTarget(const Vector2D& target) const;

	virtual void shoot();
  
	inline Gun* getCurrentGun() const { return _currentGun; }
};