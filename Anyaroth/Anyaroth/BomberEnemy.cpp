#include "BomberEnemy.h"

BomberEnemy::BomberEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, ExplosiveBulletPool* pool) : Enemy(player, g, play, texture, posIni, tag)
{
	_myBulletPool = pool;
	_bulletTexture = g->getTexture("PistolBullet");
	_attackTime = 2000;
	_life = 300;
	_speed = -8;

	_vision = 300;
	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetGravityScale(0);
}

BomberEnemy::~BomberEnemy() {}

void BomberEnemy::update(const double& deltaTime)
{
	Enemy::update(deltaTime);

	BodyComponent* _playerBody = _player->getComponent<BodyComponent>();
	b2Vec2 enemyPos = _body->getBody()->GetPosition(), playerPos = _playerBody->getBody()->GetPosition();

	double x = playerPos.x * 8 - enemyPos.x * 8, y = playerPos.y * 8 - enemyPos.y * 8;

	if (!_dead && _activated)
	{
		_body->getBody()->SetLinearVelocity({ _speed, _body->getBody()->GetLinearVelocity().y });

		if (!inCameraOnlyX() || _move)
		{
			if (_bloqueDer && playerPos.x > enemyPos.x)
			{
				_speed = _dir;
				_move = false;
				_bloqueDer = false;
			}
			else if (_bloqueIzq && playerPos.x < enemyPos.x)
			{
				_speed = -_dir;
				_move = false;
				_bloqueIzq = false;
			}
			else if (x < 0)
				_speed = -_dir;
			else
				_speed = _dir;
		}
		if(inCameraOnlyX())
		{
			if (_time >= _spawnTime)
			{
				throwBomb(Vector2D(_body->getBody()->GetPosition().x*8, _body->getBody()->GetPosition().y*8), 90, "EnemyBullet");
				_time = 0;
			}
			else
				_time += deltaTime;
		}
	}
	else
	{
		if (x < _vision && x > -_vision && y < _vision && y > -_vision)
		{
			_activated = true;
			_time = 0;
		}
	}
}

void BomberEnemy::subLife(int damage)
{
	if (!_dead)
	{
		_life.subLife(damage);
		if (_life.dead())
		{
			die();
			_hurt->die();
			_anim->playAnim(AnimatedSpriteComponent::EnemyDie);
			_body->getBody()->SetGravityScale(1);
			_dead = true;
		}
		else
			_hurt->hurt();
	}
}

void BomberEnemy::beginCollision(GameObject * other, b2Contact * contact)
{
	Enemy::beginCollision(other, contact);

	string otherTag = other->getTag();
	if (otherTag == "Ground")
	{
		double x = other->getComponent<BodyComponent>()->getBody()->GetPosition().x;
		double y = _body->getBody()->GetPosition().x;
		if (x < y)
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

void BomberEnemy::throwBomb(const Vector2D& position, const double& angle, const string& tag)
{
	Bullet* b = _myBulletPool->getUnusedObject();
	Vector2D helpPos = position;
	Vector2D bulletPos = helpPos.rotateAroundPoint(angle, position);

	if (b != nullptr)
	{
		b->init(_bulletTexture, position, 0, 10, angle, _range, tag);
		b->changeFilter();
	}
	else
	{
		Bullet* b2 = _myBulletPool->addNewBullet();
		
		b2->init(_bulletTexture, position, 0, 10, angle, _range, tag);
		b2->changeFilter();
	}
}