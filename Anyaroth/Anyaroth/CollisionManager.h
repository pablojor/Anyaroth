#pragma once

#include "GameComponent.h"
#include <list>
#include <vector>

class CollisionManager
{
	private:
		static CollisionManager* _collisionManager;

		static list<GameComponent*> _enemyBulletColliders;
		static GameComponent* player;

		CollisionManager() {}
		static bool AABBCollision(SDL_Rect rectA, SDL_Rect rectB);

	public:
		~CollisionManager();

		static CollisionManager* getCollisionManager();

		static void addEnemyBulletColliders(GameComponent* obj);
		static void addPlayer(GameComponent* obj);

		static vector<GameComponent*>::iterator checkPlayerAndBullets();

		static bool checkCollision(GameComponent* A, GameComponent* B);

		
};
