#include "MeleeEnemyComponent.h"
#include "GameComponent.h"
#include "Player.h"


MeleeEnemyComponent::MeleeEnemyComponent(GameComponent* obj) : PhysicsComponent(obj)
{
	_movement = obj->getComponent<MovingComponent>();
	if (_movement == nullptr)
		_movement = obj->addComponent<MovingComponent>();

	_anim = obj->getComponent<AnimatedSpriteComponent>();
	if (_anim == nullptr)
		_anim = obj->addComponent<AnimatedSpriteComponent>();

	_myTransform = obj->getComponent<TransformComponent>();
	if (_myTransform == nullptr)
		_myTransform = obj->addComponent<TransformComponent>();
}

void MeleeEnemyComponent::addPlayer(Player* player)
{
	_playerTransform = player->getComponent<TransformComponent>();
	if (_playerTransform == nullptr)
		_playerTransform = player->getComponent<TransformComponent>();
}

void MeleeEnemyComponent::update()
{
	Vector2D enemy, player;

	enemy = _myTransform->getPosition();
	player = _playerTransform->getPosition();

	double x, y;

	x = player.getX() - enemy.getX();
	y = player.getY() - enemy.getY();

	if (!_attacking && x < _vision && x > -_vision)
	{
		if (x > _flipRange)
		{
			_anim->unFlip();

			if (x > _attackRange)
			{
				_movement->changeDir(1, 0);
				_anim->playAnim(AnimatedSpriteComponent::Walk);
			}
			else
			{
				_movement->changeDir(0, 0);
				_anim->playAnim(AnimatedSpriteComponent::MeleeKnife); //Llamas a animacion de ataque
				_time = SDL_GetTicks();
				_attacking = true;
				cout << "attacking" << endl;
			}
		}
		else if (x < -_flipRange)
		{
			_anim->flip();

			if (x < -_attackRange)
			{
				_movement->changeDir(-1, 0);
				_anim->playAnim(AnimatedSpriteComponent::Walk);
			}
			else
			{
				_movement->changeDir(0, 0);
				_anim->playAnim(AnimatedSpriteComponent::MeleeKnife); //Llamas a animacion de ataque
				_time = SDL_GetTicks();
				_attacking = true;
				cout << "attacking" << endl;
			}
		}
	}
	else if(_attacking)
	{ 
		if (SDL_GetTicks() > _time + _attackTime)
		{
			_attacking = false;
			cout << "moving again" << endl;
			//if(colision de arma con jugador)
			//	llamas daño al jugador
		}
	}
	else
	{
		_movement->changeDir(0, 0);
		_anim->playAnim(AnimatedSpriteComponent::Idle);
	}
}