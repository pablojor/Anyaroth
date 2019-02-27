#include "MartyrEnemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "BodyComponent.h"


MartyrEnemy::MartyrEnemy(Player* player, Game* g, PlayState* play,Texture* texture, Vector2D posIni, string tag) : Enemy(player, g, play,texture, posIni, tag)
{
	_vision = 300;
	_attackRange = 25; //No se puede poner mas peque�o que la velocidad
	_attackTime = 1000;
	_life = 50;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
}

void MartyrEnemy::update()
{
	Enemy::update();

	BodyComponent* _playerBody = _player->getComponent<BodyComponent>();
	TransformComponent* _playerTransform = _player->getComponent<TransformComponent>();

	Vector2D enemy, player;

	enemy = _transform->getPosition();
	player = _playerTransform->getPosition();

	double x, y;

	x = player.getX() - enemy.getX();
	y = player.getY() - enemy.getY();

	if (!_attacking && x < _vision && x > -_vision && y < _vision && y > -_vision)
	{
		if (x > 0)
		{
			_anim->unFlip();

			if ((x > _attackRange + _playerBody->getW() * 8))
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
				_attacking = true;
			}
		}
		else if (x < 0)
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
				_attacking = true;
			}
		}
	}
	else if(_attacking)
	{ 
		if (SDL_GetTicks() > _time + _attackTime)
		{
			
			if ((x < _attackRange + _playerBody->getW() * 8 && x > -_explosionRange) && y < _explosionRange && y > -_explosionRange)
			{
				auto body = _player->getComponent<BodyComponent>()->getBody();
				body->ApplyLinearImpulseToCenter(b2Vec2(_impulse * x, _impulse * y), true);
			}

			_play->KillObject(_itList);
		}
	}
	else
	{
		_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::Idle);
	}
}