#pragma once

#include "GameComponent.h"

class TransformComponent;
class AnimatedSpriteComponent;
class PlayState;
class Camera;

class Cursor : public GameComponent
{
private:
	TransformComponent* _transform;
	AnimatedSpriteComponent* _anim;
	Camera* _cam;

	int _mouseX, _mouseY;
public:
	Cursor(Texture* texture, Game* g, PlayState* play);
	~Cursor();

	void update();
	virtual bool handleInput(const SDL_Event& event);
};
