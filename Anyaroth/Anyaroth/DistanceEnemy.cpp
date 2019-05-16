#include "DistanceEnemy.h"
#include "Game.h"
#include "BasicPistol.h"

DistanceEnemy::DistanceEnemy(Game* g, Player* player, Vector2D pos, Texture* texture, BulletPool* pool, Vector2D offset) : Enemy(g, player, pos, texture)
{
	_arm = new EnemyArm(g, this, player, this, offset);
	_arm->setTexture(g->getTexture("ArmPistol"));
	_arm->setAnimations(DefaultArmType);
	addChild(_arm);

	_myGun = new BasicPistol(g);
	_myBulletPool = pool;

	_affectedByExternalForces = true;
}

DistanceEnemy::~DistanceEnemy()
{
	if (_myBulletPool != nullptr) _myBulletPool->stopBullets();
	delete _myGun;
}

void DistanceEnemy::raycast()
{
	b2Vec2 enemyPos = _body->getBody()->GetPosition();
	b2Vec2 targetPos = _player->getComponent<BodyComponent>()->getBody()->GetPosition();

	b2RayCastInput rayInput;

	rayInput.maxFraction = 1;
	rayInput.p1 = { (float32)(enemyPos.x), (float32)(enemyPos.y - _body->getH()) };
	rayInput.p2 = { (float32)(targetPos.x), (float32)(targetPos.y) };

	b2RayCastOutput rayOutput;

	_armVision = true;

	for (b2Body* b = getWorld()->GetBodyList(); b && _armVision; b = b->GetNext())
		for (b2Fixture* f = b->GetFixtureList(); f && _armVision; f = f->GetNext())
			if ((((GameObject*)(b->GetUserData()))->getTag() == "Ground" || ((GameObject*)(b->GetUserData()))->getTag() == "Platform" ||
				((GameObject*)(b->GetUserData()))->getTag() == "Door") && f->RayCast(&rayOutput, rayInput, 0))
				_armVision = false;
}

void DistanceEnemy::shoot()
{
	if (_armVision) //Si vemos al jugador
	{
		if (_playerDistance.getX() > 0) //Derecha
			_anim->unFlip();
		else if (_playerDistance.getX() < 0) //Izquierda
			_anim->flip();

		_arm->shoot();
		_myGun->enemyShoot(_myBulletPool, _arm->getPosition(), !_anim->isFlipped() ? _arm->getAngle() + _game->random(-_fail, _fail) : _arm->getAngle() + 180 + _game->random(-_fail, _fail), "EnemyBullet");
	}
}

void DistanceEnemy::update(double deltaTime)
{
	Enemy::update(deltaTime);
	_myGun->refreshGunCadence(deltaTime);
}