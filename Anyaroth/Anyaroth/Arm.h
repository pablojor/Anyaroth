#pragma once

#include "GameComponent.h"
#include "TransformComponent.h"

class AnimatedSpriteComponent;

class Arm : public GameComponent
{
protected:
	TransformComponent* _transform;
	GameComponent* _player;
	AnimatedSpriteComponent* _anim;
public:
	Arm(Texture* texture, GameComponent* player);
	virtual ~Arm();

	void update();
};

