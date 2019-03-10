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
	Camera* _cam = nullptr;
	Vector2D _prevCamPos;
	bool _movingMouse = false;
	int _mouseX, _mouseY;

public:
	Cursor(Texture* texture, Game* g, PlayState* play);
	~Cursor() {}

	void update(double time);
	virtual bool handleInput(const SDL_Event& event);

	Vector2D getPosition();
};