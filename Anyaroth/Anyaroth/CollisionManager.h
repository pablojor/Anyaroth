#pragma once

#include "SDL.h"

class CollisionManager
{
	public:
		bool AABBCollision(SDL_Rect rectA, SDL_Rect rectB);
};