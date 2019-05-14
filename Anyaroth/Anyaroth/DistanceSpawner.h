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
		_anim->playAnim(AnimatedSpriteComponent::EnemyAttack);
		_time = 0;
	}
	else
		_time += deltaTime;

	if (_anim->getCurrentAnim() == AnimatedSpriteComponent::EnemyAttack && _anim->animationFinished())
	{
		_game->getCurrentState()->addObject(new CapsuleDistance<Spawned>(_game, _player, Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL - 40, _body->getBody()->GetPosition().y * M_TO_PIXEL), this, _spawnedPool));
		_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
		_game->getSoundManager()->playSFX("spawnerSpawn");
	}
}