#include "TutorialTurret.h"

TutorialTurret::TutorialTurret(Game* g, Player* player, Vector2D pos, BulletPool* pool) : DistanceStaticEnemy(g, player, pos, pool), Enemy(g, player, pos, g->getTexture("Turret"), "turretDeath", "turretHit", "turretMeleeHit")
{
	_vision = 1010;
	_attackRangeX = _attackRangeY = _vision; //No se puede poner mas pequeño que la velocidad
	_attackTime = 2000; //La animacion tarda unos 450

	if (_attackRangeX < _speed)
		_attackRangeX += _speed;

	_fail = 1;

	//Ajustes del arma
	_myGun->setDamage(0);
	_myGun->setMaxCadence(4000);
	_myGun->setBulletSpeed(25);

	_anim->flip();
	_hurtParticle = g->getTexture("Sparks");
}

void TutorialTurret::beginCollision(GameObject * other, b2Contact* contact)
{
	if (other->getTag() == "Bullet" || other->getTag() == "Melee")
	{
		BodyComponent* otherBody = other->getComponent<BodyComponent>();
		_contactPoint = otherBody->getBody()->GetPosition() + b2Vec2(otherBody->getW() / 2, otherBody->getH() / 2);

		if (other->getTag() == "Melee")
		{
			_game->getSoundManager()->playSFX("turretMeleeHit");
		}
		else
		{
			_game->getSoundManager()->playSFX("turretHit");
		}
	}
}

void TutorialTurret::shoot()
{
	if (_playerDistance.getX() < 0) //Izquierda
	{
		_arm->shoot();
		_myGun->enemyShoot(_myBulletPool, _arm->getPosition(), !_anim->isFlipped() ? _arm->getAngle() + _game->random(-_fail, _fail) : _arm->getAngle() + 180 + _game->random(-_fail, _fail), "EnemyBullet");

	}
}

void TutorialTurret::update(double deltaTime)
{
	DistanceEnemy::update(deltaTime);
	_body->getBody()->SetAwake(true);

	bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

	if (inVision) //Jugador en el rango
	{
		shoot();
	}
}