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
		virtual void render() const = 0;
		virtual void update() = 0;
		virtual void handleEvents(SDL_Event& e) = 0;
};
