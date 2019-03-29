#include "SpawnerEnemy.h"
#include "Capsule.h"

SpawnerEnemy::SpawnerEnemy(Game* g, Player* player, Vector2D pos) : Enemy(g, player, pos, g->getTexture("EnemyMartyr"))
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

void SpawnerEnemy::move()
{
	_body->getBody()->SetLinearVelocity({ _speed*(float32)_dir.getX(), _body->getBody()->GetLinearVelocity().y });
}

void SpawnerEnemy::dropCapsule(const double& deltaTime)
{
	if (_time >= _spawnTime && _currentEnemies < _maxEnemies)
	{
		_game->getCurrentState()->addObject(new Capsule(_game, _player, Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL), this));
		_time = 0;
	}
	else
		_time += deltaTime;
}

void SpawnerEnemy::update(const double& deltaTime)
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

void SpawnerEnemy::subLife(int damage)
{
	Enemy::subLife(damage);

	if (isDead())
		_body->getBody()->SetGravityScale(1);
}

int SpawnerEnemy::deadEnemies()
{
	int count = 0;

	for (auto o : getChildren())
	{
		if (!o->isDead())
			count++;
	}

	return count;
}