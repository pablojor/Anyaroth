#include "BomberEnemy.h"
#include "BulletEffect.h"

BomberEnemy::BomberEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool) : Enemy(g, player, pos, g->getTexture("EnemyMartyr")), _myBulletPool(pool)
{
	_bulletTexture = g->getTexture("PistolBullet");
	_damage = 10;

	_vision = 800;
	_life = 300;
	_gun = new BomberGun(g);
	_attackRangeX = 2;
	_speed = 8;
	_time = 0;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetGravityScale(0);
}

BomberEnemy::~BomberEnemy() 
{
	delete _gun;
	_gun = nullptr;
}

void BomberEnemy::shoot(const double& deltaTime)
{
	if (_time >= _shootTime)
	{
		throwBomb(Vector2D(_body->getBody()->GetPosition().x*M_TO_PIXEL, _body->getBody()->GetPosition().y*M_TO_PIXEL));
		_time = 0;
	}
	else
		_time += deltaTime;
}

void BomberEnemy::move()
{
	_body->getBody()->SetLinearVelocity({ _speed*(float32)_dir.getX(), _body->getBody()->GetLinearVelocity().y });
}

void BomberEnemy::update(const double& deltaTime)
{
	Enemy::update(deltaTime);

	bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

	if (!isDead() && inCamera() && inVision)
	{
		if (_playerDistance.getX() > _attackRangeX)
			_dir = Vector2D(1, 0);
		else if (_playerDistance.getX() < -_attackRangeX)
			_dir = Vector2D(-1, 0);
		else if (_playerDistance.getX() < _attackRangeX && _playerDistance.getX() > -_attackRangeX)
			_dir = Vector2D(0, 0);

		move();
		shoot(deltaTime);
	}
}

void BomberEnemy::subLife(int damage)
{
	Enemy::subLife(damage);

	if (isDead())
		_body->getBody()->SetGravityScale(1);
}

void BomberEnemy::throwBomb(const Vector2D& position)
{
	/*Bullet* b = _myBulletPool->getUnusedObject();
	Vector2D helpPos = position;
	Vector2D bulletPos = helpPos.rotateAroundPoint(angle, position);*/
	//b->init();
	_gun->enemyShoot(_myBulletPool, position, _angle, "EnemyBullet");

	/*if (b != nullptr)
	{
		b->init(_bulletTexture, position, 0, 10, angle, _range, tag, &_effect);
		b->init(_bulletTexture, position, 0, _damage, _angle, _range, "EnemyBullet");
		b->changeFilter(true);
	}
	else
	{
		Bullet* b2 = _myBulletPool->addNewBullet();

		b2->init(_bulletTexture, position, 0, 10, angle, _range, tag, &_effect);
		Bullet* b2 = _bulletPool->addNewBullet();
		
		b2->init(_bulletTexture, position, 0, _damage, _angle, _range, "EnemyBullet");
		b2->changeFilter();
	}*/
}