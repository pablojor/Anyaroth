#include "MeleeEnemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"


MeleeEnemy::MeleeEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy(player, g, play, texture, posIni, tag)
{
	_vision = 300;
	_attackRange = 25; //No se puede poner mas peque�o que la velocidad
	_attackTime = 800;
	_life = 50;
	_damage = 10;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false, 100);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false, 100);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	//_myCollision = new EnemyMeleeCollision(g, this, 20);
}

void MeleeEnemy::update()
{
	Enemy::update();
	if (!_dead && inCamera())
	{
		BodyComponent* _playerBody = _player->getComponent<BodyComponent>();
		//TransformComponent* _playerTransform = _player->getComponent<TransformComponent>();

		b2Vec2 enemyPos = _body->getBody()->GetPosition(),
			playerPos = _playerBody->getBody()->GetPosition();

		double x = playerPos.x * 8 - enemyPos.x * 8,
			y = playerPos.y * 8 - enemyPos.y * 8;

		if (!_attackingR && !_attackingL && x < _vision && x > -_vision && y < _vision && y > -_vision)
		{
			if (x > 0)//Derecha
			{
				_anim->unFlip();
				if (x > _attackRange)
				{
					_body->getBody()->SetLinearVelocity({ 8,_body->getBody()->GetLinearVelocity().y });
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
					_time = SDL_GetTicks();
					_attackingR = true;
					_attacking = true;
				}
			}
			else if (x < 0)//Izquierda
			{
				_anim->flip();

				if (x < -_attackRange)
				{
					_body->getBody()->SetLinearVelocity({ -8,_body->getBody()->GetLinearVelocity().y });
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
					_time = SDL_GetTicks();
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

			else if (SDL_GetTicks() > _time + _stopDmg && _attacking)
				_attacking = false;

			else if (SDL_GetTicks() > _time + _attackTime && _attacking)
			{
				if (_attackingR && (x < _attackRange + _realRange && x > 0) && y < _attackRange + _realRange && y > -_attackRange)
				{
					cout << "tas danyado" << endl; //Le haces daño
					_player->subLife(_damage);
					_attacking = false;
				}
				else if (_attackingL && (x < 0 && x > -_attackRange - _realRange) && y < _attackRange && y > -_attackRange - _realRange)
				{
					cout << "tas danyado" << endl; //Le haces daño
					_player->subLife(_damage);
					_attacking = false;
				}
			}
		}
		else
		{
			_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
			_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
		}
	}
}