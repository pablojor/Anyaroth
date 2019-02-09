#pragma once

#include <list>
#include <vector>
#include "BoxCollider.h"

class GameComponent;

class CollisionManager
{
	private:
		static CollisionManager* _collisionManager;

		CollisionManager() {}
		static bool AABBCollision(SDL_Rect rectA, SDL_Rect rectB);

	public:
		~CollisionManager();

		static CollisionManager* getCollisionManager();

		static bool checkCollision(GameComponent* A, GameComponent* B);

		
};
