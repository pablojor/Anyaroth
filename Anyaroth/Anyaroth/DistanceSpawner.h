#pragma once
#include "SpawnerEnemy.h"
#include "CapsuleDistance.h"

template<typename Spawned>
class DistanceSpawner : public SpawnerEnemy
{
private:
	BulletPool* _spawnedPool = nullptr;
public:
	DistanceSpawner(Game* g, Player* player, Vector2D pos, BulletPool* bulletPool) : SpawnerEnemy(g, player, pos), _spawnedPool(bulletPool) {};
	virtual ~DistanceSpawner() {}

	void dropCapsule(const double& deltaTime);
};

template<typename Spawned>
void DistanceSpawner<Spawned>::dropCapsule(const double& deltaTime)
{
	if (_time >= _spawnTime && _currentEnemies < _maxEnemies)
	{
		_game->getCurrentState()->addObject(new CapsuleDistance<Spawned>(_game, _player, Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL), this, _spawnedPool));
		_time = 0;
	}
	else
		_time += deltaTime;
}