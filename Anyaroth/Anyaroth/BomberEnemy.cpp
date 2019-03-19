#include "BomberEnemy.h"



BomberEnemy::BomberEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool) : Enemy(player, g, play, texture, posIni, tag)
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


BomberEnemy::~BomberEnemy()
{
}

void BomberEnemy::update(double time)
{
	Enemy::update(time);
	BodyComponent* _playerBody = _player->getComponent<BodyComponent>();

	b2Vec2 enemyPos = _body->getBody()->GetPosition(), playerPos = _playerBody->getBody()->GetPosition();

	double x = playerPos.x * 8 - enemyPos.x * 8, y = playerPos.y * 8 - enemyPos.y * 8;

	if (!_dead && _activated)
	{
		_body->getBody()->SetLinearVelocity({ _speed, _body->getBody()->GetLinearVelocity().y });

		if (!inCamera())
		{
			if (x < 0)
				_speed = -8;
			else
				_speed = 8;
		}
		else
		{
			if (_time >= _spawnTime)
			{
				//enemySpawn(new Capsule(_player, _game, _play, _game->getTexture("EnemyMelee"), Vector2D(enemyPos.x * 8 - 30 /*Numero a ajustar dependiendo del sprite*/, enemyPos.y * 8 - 25 /*Numero a ajustar dependiendo del sprite*/), "Enemy"));
				Throw(Vector2D(_body->getBody()->GetPosition().x, _body->getBody()->GetPosition().y), 90, "EnemyBullet");
				_time = 0;
			}
			else
				_time += time;
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

void BomberEnemy::Throw(const Vector2D& position, const double& angle, const string& tag)
{
	Bullet* b = _myBulletPool->getUnusedObject();
	Vector2D helpPos = position;
	Vector2D bulletPos = helpPos.rotateAroundPoint(angle, position);
	if (b != nullptr)
	{
		b->init(_bulletTexture, bulletPos, _speed, _damage, angle, _range, tag);
		b->changeFilter();
	}
	else
	{
		Bullet* b2 = _myBulletPool->addNewBullet();
		b2->init(_bulletTexture, bulletPos, _speed, _damage, angle, _range, tag);
		b2->changeFilter();
	}
}


