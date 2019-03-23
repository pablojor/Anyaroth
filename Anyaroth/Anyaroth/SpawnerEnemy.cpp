#include "SpawnerEnemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "Capsule.h"

SpawnerEnemy::SpawnerEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy(g, play, texture, posIni, tag)
{
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

void SpawnerEnemy::update(const double& deltaTime)
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
				enemySpawn(new Capsule(_player, _game, _playstate, _game->getTexture("EnemyMelee"), Vector2D(enemyPos.x * 8 - 30 /*Numero a ajustar dependiendo del sprite*/ , enemyPos.y * 8 - 25 /*Numero a ajustar dependiendo del sprite*/), "Enemy"));
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

void SpawnerEnemy::subLife(int damage)
{
	if (!_dead)
	{
		_life.subLife(damage);
		if (_life.getLife() == 0)
		{
			die();
			_anim->die();
			_anim->playAnim(AnimatedSpriteComponent::EnemyDie);
			_body->getBody()->SetGravityScale(1);

			_dead = true;
		}
		else
			_anim->hurt();
	}
}

void SpawnerEnemy::beginCollision(GameObject * other, b2Contact* contact)
{
	Enemy::beginCollision(other,contact);

	string otherTag = other->getTag();

	if (otherTag == "Suelo")
	{
		double x = other->getComponent<BodyComponent>()->getBody()->GetPosition().x;
		double y = _body->getBody()->GetPosition().x;

		if ( x < y )
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