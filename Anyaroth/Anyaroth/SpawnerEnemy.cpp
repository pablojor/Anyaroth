#include "SpawnerEnemy.h"

SpawnerEnemy::SpawnerEnemy(Game* g, Player* player, Vector2D pos) : Enemy(g, player, pos, g->getTexture("EnemyMartyr"))
{
	_vision = 800;
	_life = 40;
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

void SpawnerEnemy::update(const double& deltaTime)
{
	Enemy::update(deltaTime);

	bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

	if (!isDead() && inVision)
	{
		_currentEnemies = deadEnemies();

		if (!inCamera() || _move)
		{
			if (_bloqueDer && _playerDistance.getX() < 0)
			{
				_dir = Vector2D(-1,0);
				_move = false;
				_bloqueDer = false;
			}
			else if (_bloqueIzq && _playerDistance.getX() > 0)
			{
				_dir = Vector2D(1, 0);
				_move = false;
				_bloqueIzq = false;
			}
			else if (_playerDistance.getX() < 0)
				_dir = Vector2D(-1, 0);
			else
				_dir = Vector2D(1, 0);
		}

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

void SpawnerEnemy::beginCollision(GameObject * other, b2Contact* contact)
{
	Enemy::beginCollision(other, contact);

	string otherTag = other->getTag();

	if (otherTag == "Ground" || otherTag == "Platform")
	{
		double x = contact->GetFixtureA()->GetBody()->GetPosition().x;
		double y = _body->getBody()->GetPosition().x;

		if (x > y)
		{
			_bloqueDer = true;
			_move = true;
		}
		else
		{
			_bloqueIzq = true;
			_move = true;
		}
	}
}