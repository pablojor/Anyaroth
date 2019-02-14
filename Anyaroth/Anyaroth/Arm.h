#pragma once

#include "GameComponent.h"
#include "TransformComponent.h"
#include "Game.h"

class AnimatedSpriteComponent;

class Arm : public GameComponent
{
protected:
	TransformComponent* _transform;
	GameComponent* _player;
	AnimatedSpriteComponent* _anim;

	Game* _game; //TEMPORAL
public:
	Arm(Texture* texture, GameComponent* player, Game* g, Vector2D offset = { 0,0 });
	virtual ~Arm();

	void update();

	void setPlayer(Vector2D offset, GameComponent* player);
};

