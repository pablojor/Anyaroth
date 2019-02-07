#include "CollisionManager.h"

CollisionManager* CollisionManager::getCollisionManager()
{
	if (collisionManager == 0)
		collisionManager = new CollisionManager();

	return collisionManager;
}
