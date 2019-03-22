#pragma once
#include "GameObject.h"

class TransformComponent;
class AnimatedSpriteComponent;
class PlayState;
class Camera;

class Cursor : public GameObject
{
private:
	TransformComponent* _transform = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;

public:
	Cursor(Game* game);
	~Cursor() {}

	void update(const double& deltaTime);
};