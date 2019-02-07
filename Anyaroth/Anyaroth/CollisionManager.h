#pragma once

#include "GameComponent.h"

#include <list>

class CollisionManager
{
	private:
		static CollisionManager* _collisionManager;

		list<GameComponent*> _colliders;

		CollisionManager() {}
		static bool AABBCollision(SDL_Rect rectA, SDL_Rect rectB);

	public:
		~CollisionManager();

		static CollisionManager* getCollisionManager();

		void addCollider(GameComponent* obj) { _colliders.push_back(obj); }
		static bool checkCollision(GameComponent* A, GameComponent* B);
};

CollisionManager* CollisionManager::_collisionManager = 0;
