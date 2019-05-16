#include "BomberEnemy.h"
#include "BulletEffect.h"
#include "GameManager.h"

BomberEnemy::BomberEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool) : Enemy(g, player, pos, g->getTexture("Bomber"), "bomberDeath", "turretHit", "turretMeleeHit"), _myBulletPool(pool)
{
	_bulletTexture = g->getTexture("PistolBullet");
	_damage = 25;

	_vision = 300;
	_life = 30;
	_gun = new BomberGun(g);
	_attackRangeX = 2;
	_speed = 6;
	_time = 0;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 6, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 1, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 6, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 21, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->setW(30);
	_body->setH(20);

	_body->getBody()->SetGravityScale(0);
	_body->filterCollisions(ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);

	_hurtParticle = g->getTexture("Sparks");
}

BomberEnemy::~BomberEnemy()
{
	delete _gun;
	_gun = nullptr;
}

void BomberEnemy::shoot(double deltaTime)
{
	if (_time >= _shootTime)
	{
		throwBomb(Vector2D(_body->getBody()->GetPosition().x*M_TO_PIXEL, (_body->getBody()->GetPosition().y+_body->getH())*M_TO_PIXEL));
		_time = 0;
	}
	else
		_time += deltaTime;
}

void BomberEnemy::move()
{
	_body->getBody()->SetLinearVelocity({ _speed*(float32)_dir.getX(), _body->getBody()->GetLinearVelocity().y });
}

void BomberEnemy::update(double deltaTime)
{
	Enemy::update(deltaTime);
	_gun->refreshGunCadence(deltaTime);

	bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

	if (!isDead() && (inVision || GameManager::getInstance()->getCurrentLevel() == LevelManager::Boss3))
	{
		if (_playerDistance.getX() > _attackRangeX)
			_dir = Vector2D(1, 0);
		else if (_playerDistance.getX() < -_attackRangeX)
			_dir = Vector2D(-1, 0);
		else if (_playerDistance.getX() < _attackRangeX && _playerDistance.getX() > -_attackRangeX)
			_dir = Vector2D(0, 0);

		if (_anim->getCurrentAnim() == AnimatedSpriteComponent::EnemyAttack &&_anim->animationFinished())
		{
			_anim->playAnim(AnimatedSpriteComponent::Idle);
		}

		move();
		shoot(deltaTime);
	}
}

void BomberEnemy::subLife(int damage)
{
	Enemy::subLife(damage);

	if (isDead())
		_body->getBody()->SetGravityScale(3);
}

void BomberEnemy::throwBomb(const Vector2D& position)
{
	_gun->enemyShoot(_myBulletPool, position, _angle, "EnemyBullet");
	_anim->playAnim(AnimatedSpriteComponent::EnemyAttack);
}