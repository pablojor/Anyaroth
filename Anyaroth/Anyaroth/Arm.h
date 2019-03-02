#pragma once
#include "GameComponent.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "FollowingComponent.h"
#include "checkML.h"

#define PI 3.14159265

class PlayState;

class Arm : public GameComponent
{
protected:
	TransformComponent* _transform;
	GameComponent* _owner;
	AnimatedSpriteComponent* _anim;
	FollowingComponent* _followC;
	Camera* _cam;
public:
	Arm(Texture* texture, GameComponent* owner, Game* g, PlayState* play, Vector2D offset = { 0,0 });
	virtual ~Arm();

	Camera* getCamera() { return _cam; }; //Necesario para el ArmController
	void setOwner(Vector2D offset, GameComponent* owner);
	void setArmSprite(Texture* armTex);
};

