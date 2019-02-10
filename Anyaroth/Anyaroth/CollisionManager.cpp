#include "CollisionManager.h"
#include "GameComponent.h"

CollisionManager* CollisionManager::_collisionManager = 0;

CollisionManager::~CollisionManager()
{
	if (_collisionManager != 0)
		delete _collisionManager;
}


bool CollisionManager::_AABBCollision(SDL_Rect rectA, SDL_Rect rectB)
{
	return (rectA.x + rectA.w >= rectB.x &&
			rectA.y + rectA.h >= rectB.y &&
			rectB.x + rectB.w >= rectA.x &&
			rectB.y + rectB.h >= rectA.y);
}

//WARNING, si se usa deja basura mistica, cuidado.
//CollisionManager* CollisionManager::getCollisionManager()
//{
//	if (_collisionManager == 0)
//		_collisionManager = new CollisionManager();
//
//	return _collisionManager;
//}


bool CollisionManager::checkCollision(GameComponent* A, GameComponent* B)
{
	return _AABBCollision(A->getComponent<BoxCollider>()->getCollider(), B->getComponent<BoxCollider>()->getCollider());
}
