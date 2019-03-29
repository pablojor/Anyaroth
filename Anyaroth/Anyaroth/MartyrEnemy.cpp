#include "MartyrEnemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "BodyComponent.h"

MartyrEnemy::MartyrEnemy(Game* g, Player* player, Vector2D pos) : GroundEnemy(g, player, pos, g->getTexture("EnemyMartyr")), Enemy(g, player, pos, g->getTexture("EnemyMartyr"))
{
	_vision = 300;
	_life = 50;
	_damage = 80;
	_speed = 20;
	_attackRangeX = 25; //No se puede poner mas pequeño que la velocidad
	_attackRangeY = 20;
	_attackTime = 850;

	if (_attackRangeX < _speed)
		_attackRangeX += _speed;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 14, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 5, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 23, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 10, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->setW(22);
	_body->setH(15);
	_body->moveShape(b2Vec2(0.3, _body->getH() + 0.1));
	_body->filterCollisions(ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);

	_body->addCricleShape(b2Vec2(0.4, _body->getH() + _body->getH() * 2 / 3), _body->getH() + _body->getH() / 3, ENEMIES, FLOOR | PLATFORMS);
}

void MartyrEnemy::update(const double& deltaTime)
{
	Enemy::update(deltaTime);

	if (!isDead() && inCamera())
	{
		bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;
		bool sameFloor = _playerDistance.getY() < _attackRangeY && _playerDistance.getY() > -_attackRangeY;

		if (!_attacking && inVision)
		{
			if (_playerDistance.getX() > 0) //Derecha
			{
				_anim->unFlip();
				_dir = Vector2D(1, 0);

				if (_playerDistance.getX() > _attackRangeX)
					moving(_dir);
				else if(sameFloor)
					attack();
				else idle();
			}
			else if (_playerDistance.getX() < 0) //Izquierda
			{
				_anim->flip();
				_dir = Vector2D(-1, 0);

				if (_playerDistance.getX() < -_attackRangeX)
					moving(_dir);
				else if (sameFloor)
					attack();
				else
					idle();
			}
		}
		else if(_attacking)
			attacking(deltaTime);
		else
			idle();
	}
}

void MartyrEnemy::explosionDie()
{
	_anim->die();
	setDead(true);
	_body->filterCollisions(DEAD_ENEMIES, FLOOR | PLATFORMS);
}

void MartyrEnemy::attacking(const double& deltaTime)
{
	bool maxRange = _playerDistance.getX() < _explosionRange && _playerDistance.getX() > -_explosionRange && _playerDistance.getY() < _explosionRange && _playerDistance.getY() > -_explosionRange;
	bool midleRange = _playerDistance.getX() < _explosionRange / 2 && _playerDistance.getX() > -_explosionRange / 2 && _playerDistance.getY() < _explosionRange / 2 && _playerDistance.getY() > -_explosionRange / 2;
	bool sameFloor = _playerDistance.getY() < _attackRangeY && _playerDistance.getY() > -_attackRangeY;

	if (_attacking)
	{
		if (_time > _attackTime && sameFloor && maxRange)
		{
			auto body = _player->getComponent<BodyComponent>()->getBody();

			if (midleRange)
				body->ApplyLinearImpulseToCenter(b2Vec2(_impulse * _playerDistance.getX() * 3, _impulse * _playerDistance.getY() * 2), true);
			else
				body->ApplyLinearImpulseToCenter(b2Vec2(_impulse * _playerDistance.getX(), _impulse * _playerDistance.getY()), true);

			_player->subLife(_damage);
			_attacking = false;
			explosionDie();
		}
		else if (_anim->animationFinished())
		{
			_attacking = false;
			explosionDie();
		}
		_time += deltaTime;
	}
}