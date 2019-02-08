#include "CollisionManager.h"

CollisionManager* CollisionManager::_collisionManager = 0;

CollisionManager::~CollisionManager()
{
	if (_collisionManager != 0)
		delete _collisionManager;
}


bool CollisionManager::AABBCollision(SDL_Rect rectA, SDL_Rect rectB)
{
	return (rectA.x + rectA.w >= rectB.x &&
			rectA.y + rectA.h >= rectB.y &&
			rectB.x + rectB.w >= rectA.x &&
			rectB.y + rectB.h >= rectA.y);
}

CollisionManager* CollisionManager::getCollisionManager()
{
	if (_collisionManager == 0)
		_collisionManager = new CollisionManager();

	return _collisionManager;
}

void CollisionManager::addEnemyBulletColliders(GameComponent* obj)
{
	_enemyBulletColliders.push_back(obj);
}

void CollisionManager::addPlayer(GameComponent* obj)
{
	player = obj;
}

vector<GameComponent*>::iterator CollisionManager::checkPlayerAndBullets()
{
	list<GameComponent*>::iterator it = _enemyBulletColliders.begin();

	vector <list<GameComponent*>::iterator> bullets;

	for (GameComponent* o : _enemyBulletColliders)
	{
		if (checkCollision(player, o))
		{
			bullets.push_back(o.get);
		}
	}

}


bool CollisionManager::checkCollision(GameComponent* A, GameComponent* B)
{
	return AABBCollision(A->collider->getCollider(), B->collider->getCollider());
}
