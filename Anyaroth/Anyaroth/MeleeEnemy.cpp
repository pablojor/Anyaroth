#include "MeleeEnemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"

MeleeEnemy::MeleeEnemy(Game* g, PlayState* playstate, Texture* texture, Vector2D posIni, string tag) : Enemy(g, playstate, texture, posIni, tag)
{
	_vision = 300;
	_life = 50;
	_damage = 10;
	_speed = 8;
	_attackRangeX = 25; //No se puede poner mas pequeño que la velocidad
	_attackRangeY = 15;
	_attackTime = 800;

	if (_attackRangeX < _speed)
		_attackRangeX += _speed;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false, 100);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR);
}

void MeleeEnemy::update(const double& deltaTime)
{
	Enemy::update(deltaTime);

	if (!_dead && inCamera())
	{
		bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;
		bool sameFloor = _playerDistance.getY() < _attackRangeY && _playerDistance.getY() > -_attackRangeY;

		if (inVision && sameFloor)
		{
			if (_playerDistance.getX() > 0) //Derecha
			{
				_anim->unFlip();
				_dir = Vector2D(1, 0);

				if (_playerDistance.getX() > _attackRangeX)
					moving(_dir);
				else
					attack();
			}
			else if (_playerDistance.getX() < 0) //Izquierda
			{
				_anim->flip();
				_dir = Vector2D(-1, 0);

				if (_playerDistance.getX() < -_attackRangeX)
					moving(_dir);
				else
					attack();
			}
			attacking(deltaTime);
		}
		else
		{
			idle();
		}
	}
}
void MeleeEnemy::idle()
{
	_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
	_anim->playAnim(AnimatedSpriteComponent::Idle);
	_attacking = false;
}

void MeleeEnemy::moving(Vector2D& dir)
{
	if (_attacking == false)
	{
		_body->getBody()->SetLinearVelocity({ _speed*(float32)dir.getX(), _body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::EnemyWalk);
	}
}

void MeleeEnemy::attack()
{
	if (_attacking == false)
	{
		_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::EnemyAttack); //Llamas a animacion de ataque
		_time = 0;
		_attacking = true;
	}
}

void MeleeEnemy::attacking(const double& deltaTime)
{
	bool attackRangeLeft = _playerDistance.getX() < 0 && _playerDistance.getX() > -_attackRangeX - _realRange;
	bool attackRangeRight = _playerDistance.getX() > 0 && _playerDistance.getX() < _attackRangeX + _realRange;
	bool sameFloor = _playerDistance.getY() < _attackRangeY && _playerDistance.getY() > -_attackRangeY;

	if (_attacking)
	{
		if (_time > _attackTime && sameFloor && (attackRangeLeft || attackRangeRight))
		{
			_player->subLife(_damage);
			_attacking = false;
		}
		else if (_anim->animationFinished())
			_attacking = false;

		_time += deltaTime;
	}
}