#pragma once

#include "GameComponent.h"
#include "TransformComponent.h"

class AnimatedSpriteComponent;
class Player;

class Arm : public GameComponent
{
protected:
	TransformComponent* _transform;
	GameComponent* _player;
	AnimatedSpriteComponent* _anim;
public:
	Arm(Texture* texture, GameComponent* player, Vector2D offset = { 0,0 });
	virtual ~Arm();

	void update();

	void setPlayer(Vector2D offset, GameComponent* player);
};

