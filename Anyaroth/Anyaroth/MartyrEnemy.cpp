#include "MartyrEnemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "GameManager.h"
#include "BodyComponent.h"

MartyrEnemy::MartyrEnemy(Game* g, Player* player, Vector2D pos) : GroundEnemy(g, player, pos, g->getTexture("EnemyMartyr")), Enemy(g, player, pos, g->getTexture("EnemyMartyr"), "martyrDie","martyrHit", "martyrMeleeHit")
{
	_vision = 300;
	_life = 25;
	_damage = 35;
	_speed = 12;
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

	_body->setW(25);
	_body->setH(15);

	_body->moveShape(b2Vec2(0.3, _body->getH() + 0.1));
	_body->filterCollisions(ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);
	_body->addCricleShape(b2Vec2(0.4, _body->getH() + _body->getH() * 2 / 3), _body->getH() + _body->getH() / 3, ENEMIES, FLOOR | PLATFORMS);

	addSensors();
}

void MartyrEnemy::update(double deltaTime)
{
	Enemy::update(deltaTime);

	if (!isStunned() && !isDead() && (inCamera() || GameManager::getInstance()->getCurrentLevel() == LevelManager::Boss3))
	{
		bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;
		bool sameFloor = _playerDistance.getY() < _attackRangeY && _playerDistance.getY() > -_attackRangeY;

		if (!_attacking && (inVision || GameManager::getInstance()->getCurrentLevel() == LevelManager::Boss3))
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

	_game->getSoundManager()->playSFX("martyrExplosion");
}

void MartyrEnemy::attacking(double deltaTime)
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
			_game->getCurrentState()->getMainCamera()->shake(2, 500);
			explosionDie();
		}
		else if (_time > _attackTime)
		{
			_attacking = false;
			explosionDie();
			_game->getCurrentState()->getMainCamera()->shake(2, 500);
		}
		_time += deltaTime;
	}
}