#pragma once
#include "Texture.h"

class Camera;

class BackGround
{
protected:
	Texture * _texture = nullptr;
	SDL_Rect _mainRect;

public:
	BackGround(Texture* texture, Camera* camera);
	virtual ~BackGround() {};

	virtual void render() const = 0;
	virtual void update() = 0 {};
};

