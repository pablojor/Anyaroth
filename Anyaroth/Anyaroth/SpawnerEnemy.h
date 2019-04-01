#pragma once
#include "Enemy.h"
#include "CapsuleNormal.h"
#include "CapsuleDistance.h"

template<typename Spawned>
class SpawnerEnemy : public Enemy
{
private:
	double _spawnTime = 5000, _maxEnemies = 4, _currentEnemies = 0;
	Vector2D _dir = Vector2D();
	bool _distance = false;
	BulletPool* _spawnedPool = nullptr;

public:
	SpawnerEnemy(Game* g, Player* player, Vector2D pos, bool distance= false, BulletPool* bulletPool= nullptr);
	virtual ~SpawnerEnemy() {}

	void move();
	void dropCapsule(const double& deltaTime);

	int deadEnemies();
	virtual void update(const double& deltaTime);
	virtual void subLife(int damage);
};

template<typename Spawned>
SpawnerEnemy<Spawned>::SpawnerEnemy(Game* g, Player* player, Vector2D pos, bool distance, BulletPool* bulletPool) : Enemy(g, player, pos, g->getTexture("EnemyMartyr")), _distance(distance), _spawnedPool(bulletPool)
{
	_vision = 800;
	_life = 300;
	_attackRangeX = 2;
	_speed = 8;
	_time = 0;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetGravityScale(0);
}
template<typename Spawned>
void SpawnerEnemy<Spawned>::move()
{
	_body->getBody()->SetLinearVelocity({ _speed*(float32)_dir.getX(), _body->getBody()->GetLinearVelocity().y });
}
template<typename Spawned>
void SpawnerEnemy<Spawned>::dropCapsule(const double& deltaTime)
{
	if (_time >= _spawnTime && _currentEnemies < _maxEnemies)
	{
		if (!_distance)
			_game->getCurrentState()->addObject(new CapsuleNormal<Spawned>(_game, _player, Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL), this));
		else
			_game->getCurrentState()->addObject(new CapsuleDistance<Spawned>(_game, _player, Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL), this, _spawnedPool));
		_time = 0;
	}
	else
		_time += deltaTime;
}
template<typename Spawned>
void SpawnerEnemy<Spawned>::update(const double& deltaTime)
{
	Enemy::update(deltaTime);

	bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

	if (!isDead() && inCamera() && inVision)
	{
		_currentEnemies = deadEnemies();

		if (_playerDistance.getX() > _attackRangeX)
			_dir = Vector2D(1, 0);
		else if (_playerDistance.getX() < -_attackRangeX)
			_dir = Vector2D(-1, 0);
		else if (_playerDistance.getX() < _attackRangeX && _playerDistance.getX() > -_attackRangeX)
			_dir = Vector2D(0, 0);

		move();
		dropCapsule(deltaTime);
	}
}
template<typename Spawned>
void SpawnerEnemy<Spawned>::subLife(int damage)
{
	Enemy::subLife(damage);

	if (isDead())
		_body->getBody()->SetGravityScale(1);
}
template<typename Spawned>
int SpawnerEnemy<Spawned>::deadEnemies()
{
	int count = 0;

	for (auto o : getChildren())
	{
		if (!o->isDead())
			count++;
	}

	return count;
}