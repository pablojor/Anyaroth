#pragma once

#include "SDL.h"
#include "GameComponent.h"

#include <string>

class CollisionHandler
{
	public:
		bool AABBCollision(SDL_Rect rectA, SDL_Rect rectB);
		string Collision(GameComponent* A, GameComponent* B);
};