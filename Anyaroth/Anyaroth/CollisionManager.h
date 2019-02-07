#pragma once

class CollisionManager
{
	private:
		static CollisionManager* collisionManager;
		CollisionManager() {}

	public:
		static CollisionManager* getCollisionManager();
};

CollisionManager* CollisionManager::collisionManager = 0;
