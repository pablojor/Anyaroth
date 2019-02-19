#include "MartyrEnemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "BodyComponent.h"


MartyrEnemy::MartyrEnemy(Player* player, Game* g, PlayState* play,Texture* texture, Vector2D posIni) : _player(player), Enemy(player, g, play,texture, posIni)
{
	_vision = 300;
	_flipRange = 5;
	_attackRange = 25; //No se puede poner mas pequeño que la velocidad
	_attackTime = 1000;
	_life = 50;
}

void MartyrEnemy::update()
{
	Enemy::update();

	Vector2D enemy, player;

	enemy = _transform->getPosition();
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
			
			if ((x < _explosionRange && x > 0) || (x > -_explosionRange && x < 0) && (y < _explosionRange && y > 0) || (y > -_explosionRange && y < 0))
			{
				auto body = _player->getComponent<BodyComponent>()->getBody();
				body->ApplyLinearImpulseToCenter(b2Vec2(_impulse * x, _impulse * y), true);
			}

			_play->KillObject(_itList);
		}
	}
	else
	{
		_movement->changeDir(0, 0);
		_anim->playAnim(AnimatedSpriteComponent::Idle);
	}
}