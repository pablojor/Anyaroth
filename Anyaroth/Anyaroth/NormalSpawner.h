#pragma once
#include "SpawnerEnemy.h"
#include "CapsuleNormal.h"

template<typename Spawned>
class NormalSpawner : public SpawnerEnemy
{
public:
	NormalSpawner(Game* g, Player* player, Vector2D pos) : SpawnerEnemy(g, player, pos) {};
	virtual ~NormalSpawner() {}

	void dropCapsule(double deltaTime);
};

template<typename Spawned>
void NormalSpawner<Spawned>::dropCapsule(double deltaTime)
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
		_game->getCurrentState()->addObject(new CapsuleNormal<Spawned>(_game, _player, Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL- 40, _body->getBody()->GetPosition().y * M_TO_PIXEL), this));
		_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
		_game->getSoundManager()->playSFX("spawnerSpawn");
	}
}