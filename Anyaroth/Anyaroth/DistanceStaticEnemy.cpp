#include "DistanceStaticEnemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include"Game.h"

DistanceStaticEnemy::DistanceStaticEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool) : DistanceEnemy(g, player, pos, g->getTexture("Turret"), pool), Enemy(g, player, pos, g->getTexture("Turret"), "turretDeath", "turretHit", "turretMeleeHit")
{
	_vision = 500;
	_life = 12;
	_attackRangeX = _attackRangeY = _vision; //No se puede poner mas pequeño que la velocidad
	_attackTime = 2000; //La animacion tarda unos 450

	if (_attackRangeX < _speed)
		_attackRangeX += _speed;

	_myGun->setBulletAnimType(TurretBullet);
	_myGun->setBulletTexture(g->getTexture("TurretBullet"));

	_arm->setTexture(g->getTexture("TurretArm"));
	_arm->setAnimations(TurretArmType);

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 12, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 8, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 13, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	//_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLATFORMS);

	_body->setW(20);
	_body->setH(20);

	_body->moveShape(b2Vec2(0, 0.1));
	_body->filterCollisions(ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);

	//Ajustes del arma
	_myGun->setDamage(2);
	_myGun->setMaxCadence(700);
	_myGun->setBulletSpeed(30);
	_myGun->setShotSound("turretShot");
	_hurtParticle = g->getTexture("Sparks");
	_affectedByExternalForces = false;
}

void DistanceStaticEnemy::update(double deltaTime)
{
	DistanceEnemy::update(deltaTime);
	_body->getBody()->SetAwake(true);

	if (!isStunned() && !isDead() && inCamera())
	{
		bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

		if (inVision) //Jugador en el rango
		{
			raycast();
			shoot();
		}
	}
}

void DistanceStaticEnemy::die()
{
	Enemy::die();
	_arm->setActive(false);
}