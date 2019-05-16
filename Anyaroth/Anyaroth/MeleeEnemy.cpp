#include "MeleeEnemy.h"
#include "GameObject.h"
#include "GameManager.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"

MeleeEnemy::MeleeEnemy(Game* g, Player* player, Vector2D pos) : GroundEnemy(g, player, pos, g->getTexture("EnemyMelee")), Enemy(g, player, pos, g->getTexture("EnemyMelee"), "meleeDeath", "meleeHit", "meleeEnemyHit")
{
	_vision = 300;
	_life = 10;
	_damage = 15;
	_speed = 8;
	_attackRangeX = 40; //No se puede poner mas pequeño que la velocidad
	_attackRangeY = 30;
	_attackTime = 800;

	if (_attackRangeX < _speed)
		_attackRangeX += _speed;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false, 100);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->addCricleShape(b2Vec2(0, _body->getH() - 0.5 +_body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLATFORMS);

	addSensors();
}

void MeleeEnemy::update(double deltaTime)
{
	Enemy::update(deltaTime);

	if (!isStunned() && !isDead() && (inCamera() || GameManager::getInstance()->getCurrentLevel() == LevelManager::Boss3))
	{
		bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;
		bool sameFloor = _playerDistance.getY() < _attackRangeY && _playerDistance.getY() > -_attackRangeY;

		if (inVision || GameManager::getInstance()->getCurrentLevel() == LevelManager::Boss3)
		{
			if (abs(_playerDistance.getX()) > 0)
			{
				_playerDistance.getX() > 0 ? _dir = Vector2D(1, 0) : _dir = Vector2D(-1, 0);
				_dir.getX() > 0 ? _anim->unFlip() : _anim->flip();

				if (abs(_playerDistance.getX()) > _attackRangeX)
					moving(_dir);
				else if (sameFloor)
					attack();
			}
			attacking(deltaTime);
		}
		else
			idle();
	}
}

void MeleeEnemy::idle()
{
	if (_attacking == true && _anim->animationFinished())
		_attacking = false;

	GroundEnemy::idle();
}

void MeleeEnemy::attacking(double deltaTime)
{
	bool attackRangeLeft = _playerDistance.getX() < 0 && _playerDistance.getX() > -_attackRangeX;
	bool attackRangeRight = _playerDistance.getX() > 0 && _playerDistance.getX() < _attackRangeX;
	bool sameFloor = _playerDistance.getY() < _attackRangeY && _playerDistance.getY() > -_attackRangeY;

	if (_attacking)
	{
		if (_time > _attackTime && sameFloor && (attackRangeLeft || attackRangeRight))
		{
			_player->subLife(_damage);
			_attacking = false;
		}
		else if (_anim->animationFinished())
		{
			_attacking = false;
			idle();
		}

		_time += deltaTime;
	}
}