#pragma once
#include "GameComponent.h"

class TransformComponent;
class AnimatedSpriteComponent;
class PlayState;
class Camera;

class Cursor : public GameComponent
{
private:
	TransformComponent* _transform = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;

public:
	Cursor(Game* game);
	~Cursor() {}

	void update(double time);
};