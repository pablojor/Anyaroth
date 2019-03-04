#include "DistanceDynamicEnemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"

DistanceDynamicEnemy::DistanceDynamicEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : DistanceEnemy(player, g, play, texture, posIni, tag)
{
	_vision = 200;
	_attackRange = 120; //No se puede poner mas peque�o que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450
	_life = 50;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
}

void DistanceDynamicEnemy::update()
{
	Enemy::update();

	BodyComponent* _playerBody = _player->getComponent<BodyComponent>();

	b2Vec2 enemyPos = _body->getBody()->GetPosition(),
		playerPos = _playerBody->getBody()->GetPosition();

	double x = playerPos.x * 8 - enemyPos.x * 8,
		y = playerPos.y * 8 - enemyPos.y * 8;

	if (!_attacking && x < _vision && x > -_vision && y < _vision && y > -_vision) //Me acerco al jugador
	{
		//-----MOVERSE HACIA EL JUGADOR
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
				_anim->playAnim(AnimatedSpriteComponent::Idle);
				_time = SDL_GetTicks();
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
				_anim->playAnim(AnimatedSpriteComponent::Idle);
				_time = SDL_GetTicks();
				_attacking = true;
			}
		}
		//-------------
		
	}
	else if (_attacking) //Ya estoy a una distancia optima, ataco al jugador
	{
		if (x < -_attackRange || x > _attackRange || y < -_attackRange || y > _attackRange) //Si has perdido de vista al jugador dejas de atacar
			_attacking = false;
		else
		{
			RayCast();

			if (_armVision) //Si vemos al jugador
			{
				if (x > 0) //Derecha
					_anim->unFlip();
				else if (x < 0) //Izquierda
					_anim->flip();

				_arm->shoot();
			}
			else
			{
				_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
			}
		}
	}
	else //Me quedo respirando y tranquilito
	{
		_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	}
}
