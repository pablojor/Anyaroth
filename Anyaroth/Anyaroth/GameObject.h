#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

class GameObject
{
	private:
	public:
		virtual ~GameObject() {};
		virtual void render(Uint32 time) = 0;
		virtual void update(Uint32 time) = 0;
		virtual void handleInput(Uint32 time, const SDL_Event& event) = 0;
};
