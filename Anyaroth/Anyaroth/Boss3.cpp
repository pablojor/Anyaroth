#include "Boss3.h"
#include "ImprovedRifle.h"

Boss3::Boss3(Game * g, Player * player, Vector2D pos, BulletPool * pool) : Boss(g, player, pos, pool, g->getTexture("EnemyMartyr")), Enemy(g, player, pos, g->getTexture("EnemyMartyr"))
{
	_life = 250; // Demo Guerrilla
	_life1 = _life2 = _life3 = _life;

	delete(_myGun);
	_myGun = new ImprovedRifle(g);
	_myGun->setMaxCadence(0);
	_myGun->setBulletSpeed(8);
	_myGun->setDamage(1);


	_gravGun = new GravityBombCannon(g);
	_gravGun->setMaxCadence(0);

	_body->setW(12);
	_body->setH(26);

	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);

	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR | PLATFORMS);
	_body->getBody()->SetFixedRotation(true);


	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 3 / M_TO_PIXEL, b2Vec2(0, 3), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);

	_playerBody = _player->getComponent<BodyComponent>();

	_actualState = Moving;
}

Boss3::~Boss3()
{
}

void Boss3::movement(const double& deltaTime)
{
	if (_actualState == Moving)
	{
		_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
		_playerPos = Vector2D(_playerBody->getBody()->GetPosition().x * M_TO_PIXEL, _playerBody->getBody()->GetPosition().y * M_TO_PIXEL);

		double pos = _body->getBody()->GetPosition().x* M_TO_PIXEL;
		_dir = (pos >= _playerPos.getX()) ? -1 : 1;

		double range = _playerPos.getX() + _playerBody->getW() / 2 - _bodyPos.getX() + _body->getW() / 2;

		if (_dir == 1)
			_anim->unFlip();
		else
			_anim->flip();

		if (range <= -_stopRange || range >= _stopRange)
			_body->getBody()->SetLinearVelocity(b2Vec2(_velocity * _dir / M_TO_PIXEL, _body->getBody()->GetLinearVelocity().y));
	}
}


void Boss3::fase1(const double& deltaTime)
{
	if (_actualState == Shooting)
			circularShoot(deltaTime);
	else
	{
		if (_noAction > _doSomething)
		{
			if (_game->random(0, 100) > 30)
			{
				circularShoot(deltaTime);
				_noAction = 0;
				_actualState = Shooting;
			}
			else
			{
				shootGrav();
				_noAction = 0;
			}
		}
		else
			_noAction += deltaTime;
	}
}

void Boss3::circularShoot(const double& deltaTime)
{
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_timeOnShooting += deltaTime;
	_armVision = false;

	if (_actualBullet == 0 && _num == 3)
	{
		_actualState = Moving;
		_armVision = true;
		_timeBeetwenBullets = 0;
		_doSomething = _game->random(1500, 3000);
		_num = 0;
		_timeOnShooting = 0;
	}
	else
	{	
		if (_timeOnShooting >= _timeBeetwenBullets)		
			shootBullet();		
	}
}

void Boss3::shootBullet()
{
	for (int i = 0; i < _numBullets; i++)
	{
		shoot();
		_angle += _angleIncrease;
		_actualBullet++;
	}

	_timeBeetwenBullets += _timeBeetwenCircularShoot;
	_num++;
	_actualBullet = 0;	
}

void Boss3::shoot()
{
	_myGun->enemyShoot(_myBulletPool, _bodyPos, _angle, "EnemyBullet");
}

void Boss3::shootGrav()
{
	_arm->shoot();
	_gravGun->enemyShoot(_myBulletPool, _arm->getPosition(), !_anim->isFlipped() ? _arm->getAngle() + _game->random(-_fail, _fail) : _arm->getAngle() + 180 + _game->random(-_fail, _fail), "EnemyBullet");
	_doSomething = _game->random(1500, 3000);
}