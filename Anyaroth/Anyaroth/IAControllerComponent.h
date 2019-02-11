#pragma once

#include "PhysicsComponent.h"
#include "MovingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "TransformComponent.h"

class GameComponent;
class Player;

class IAControllerComponent : public PhysicsComponent
{
private:
	AnimatedSpriteComponent* _anim;
	MovingComponent* _movement = nullptr;
	TransformComponent* _myTransform = nullptr;
	TransformComponent* _playerTransform = nullptr;
	

public:
	IAControllerComponent(GameComponent* obj);

	void addPlayer(Player* player);
	virtual void update();
};