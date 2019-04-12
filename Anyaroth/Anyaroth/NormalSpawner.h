#pragma once
#include "SpawnerEnemy.h"
#include "CapsuleNormal.h"

template<typename Spawned>
class NormalSpawner : public SpawnerEnemy
{
public:
	NormalSpawner(Game* g, Player* player, Vector2D pos) : SpawnerEnemy(g, player, pos) {};
	virtual ~NormalSpawner() {}

	void dropCapsule(const double& deltaTime);
};

template<typename Spawned>
void NormalSpawner<Spawned>::dropCapsule(const double& deltaTime)
{
	if (_time >= _spawnTime && _currentEnemies < _maxEnemies)
	{
		_game->getCurrentState()->addObject(new CapsuleNormal<Spawned>(_game, _player, Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL), this));
		_time = 0;
	}
	else
		_time += deltaTime;
}