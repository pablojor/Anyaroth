#include "DistanceDynamicEnemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "BasicPistol.h"

DistanceDynamicEnemy::DistanceDynamicEnemy(Game* g, Player* player, Vector2D pos, BulletPool* pool) : DistanceEnemy(g, player, pos, g->getTexture("Trooper"), pool, {27,16}), GroundEnemy(g, player, pos, g->getTexture("Trooper")), Enemy(g, player, pos, g->getTexture("Trooper"), "meleeDeath", "meleeHit", "meleeEnemyHit")
{
	_vision = 300;
	_life = 12;
	_speed = 8;
	_attackRangeX = _attackRangeY = _vision / 2; //No se puede poner mas pequeño que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450

	_myGun = new BasicPistol(g);

	if (_attackRangeX < _speed)
		_attackRangeX += _speed;

	//_myGun->setBulletAnimType(TurretBullet);
	//_myGun->setBulletTexture(g->getTexture("PistolBullet"));

	_arm->setTexture(g->getTexture("TrooperArm"));
	_arm->setAnimations(TrooperArmType);

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 16, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 16, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 35, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	_body->setH(26);
	_body->moveShape(b2Vec2(0, -1));
	_body->addCricleShape(b2Vec2(0, _body->getH() - 0.5 + _body->getH() / 20 - 0.5), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLATFORMS);
	//_body->addCricleShape(b2Vec2(0, _body->getH() - 0.5 + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLATFORMS);
	_body->filterCollisions(ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);
	
	//_body->moveShape(b2Vec2(0, 0));
	addSensors();

	//Ajustes del arma
	_myGun->setDamage(2);
	_myGun->setMaxCadence(700);
	_myGun->setBulletSpeed(30);
}

void DistanceDynamicEnemy::update(const double& deltaTime)
{
	DistanceEnemy::update(deltaTime);

	if (!isStunned() && !isDead() && inCamera())
	{
		bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

		if (!_attacking && inVision) //Me acerco al jugador
		{
			if (_playerDistance.getX() > 0)//Derecha
			{
				_anim->unFlip();
				_dir = Vector2D(1, 0);

				if (_playerDistance.getX() > _attackRangeX)
					moving(_dir);
				else
					attack();
			}
			else if (_playerDistance.getX() < 0)//Izquierda
			{
				_anim->flip();
				_dir = Vector2D(-1, 0);

				if (_playerDistance.getX() < -_attackRangeX)
					moving(_dir);
				else
					attack();
			}
		}
		else if (_attacking) //Ya estoy a una distancia optima, ataco al jugador
			attacking(deltaTime);
		else
			idle();
	}
}

void DistanceDynamicEnemy::attacking(const double& deltaTime)
{
	bool outRange = _playerDistance.getX() < -_attackRangeX || _playerDistance.getX() > _attackRangeX || _playerDistance.getY() < -_attackRangeY || _playerDistance.getY() > _attackRangeY;

	if (outRange) //Si has perdido de vista al jugador dejas de atacar
		_attacking = false;
	else
	{
		raycast();
		shoot();

		if(!_armVision && !isStunned())
			_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
	}
}

void DistanceDynamicEnemy::die()
{
	Enemy::die();
	_arm->setActive(false);
}

void DistanceDynamicEnemy::addSensors()
{
	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 2 / M_TO_PIXEL, b2Vec2(-2, 0), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	fDef.friction = -26;
	_body->addFixture(&fDef, this);

	shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 2 / M_TO_PIXEL, b2Vec2(2, 0), 0);
	fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	fDef.friction = 26;
	_body->addFixture(&fDef, this);
}