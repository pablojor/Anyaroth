#include "MeleeEnemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"

MeleeEnemy::MeleeEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy(player, g, play, texture, posIni, tag)
{
	_vision = 300;
	_attackRange = 25; //No se puede poner mas pequeño que la velocidad
	_attackTime = 800;
	_life = 50;
	_damage = 10;
	_speed = 8;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false, 100);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR);
}

void MeleeEnemy::update(double time)
{
	Enemy::update(time);
	if (!_dead && inCamera())
	{
		
		BodyComponent* _playerBody = _player->getComponent<BodyComponent>();

		b2Vec2 enemyPos = _body->getBody()->GetPosition(), playerPos = _playerBody->getBody()->GetPosition();

		double x = playerPos.x * 8 - enemyPos.x * 8, y = playerPos.y * 8 - enemyPos.y * 8;

		if (!_attackingR && !_attackingL && x < _vision && x > -_vision && y < _vision && y > -_vision)
		{
			if (x > 0)//Derecha
			{
				_anim->unFlip();
				if (x > _attackRange)
				{
					_body->getBody()->SetLinearVelocity({ _speed,_body->getBody()->GetLinearVelocity().y });
					_anim->playAnim(AnimatedSpriteComponent::EnemyWalk);
				}
				else if (y > _attackRange || y < -_attackRange)
				{
					_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
					_anim->playAnim(AnimatedSpriteComponent::Idle);
				}
				else
				{
					_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
					_anim->playAnim(AnimatedSpriteComponent::EnemyAttack); //Llamas a animacion de ataque
					_time = 0;
					_attackingR = true;
					_attacking = true;
				}
			}
			else if (x < 0)//Izquierda
			{
				_anim->flip();

				if (x < -_attackRange)
				{
					_body->getBody()->SetLinearVelocity({ -_speed,_body->getBody()->GetLinearVelocity().y });
					_anim->playAnim(AnimatedSpriteComponent::EnemyWalk);
				}
				else if (y > _attackRange || y < -_attackRange)
				{
					_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
					_anim->playAnim(AnimatedSpriteComponent::Idle);
				}
				else
				{
					_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
					_anim->playAnim(AnimatedSpriteComponent::EnemyAttack); //Llamas a animacion de ataque
					_time = 0;
					_attackingL = true;
					_attacking = true;
				}
			}
		}
		else if (_attackingR || _attackingL)
		{
			if (_anim->animationFinished())
			{
				_attackingR = _attackingL = _attacking = false;
				_anim->playAnim(AnimatedSpriteComponent::Idle);
			}
			else if (_time > _stopDmg && _attacking)
			//else if (time > _time + _stopDmg && _attacking)
				_attacking = false;
			else if (_time > _attackTime && _attacking)
			//else if (time > _time + _attackTime && _attacking)
			{
				if (_attackingR && (x < _attackRange + _realRange && x > 0) && y < _attackRange + _realRange && y > -_attackRange)
				{
					_player->subLife(_damage);
					_attacking = false;
				}
				else if (_attackingL && (x < 0 && x > -_attackRange - _realRange) && y < _attackRange && y > -_attackRange - _realRange)
				{
					_player->subLife(_damage);
					_attacking = false;
				}
			}
			_time += time;
		}
		else
		{
			_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
			_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
		}
	}
}