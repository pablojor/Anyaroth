#pragma once
#include "Texture.h"
#include "Vector2D.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

class Camera;

class GameObject
{
public:
	virtual ~GameObject() {}
	virtual void render(Camera* c) const = 0;
	virtual void update() = 0;
	virtual bool handleInput(const SDL_Event& event) = 0;
};