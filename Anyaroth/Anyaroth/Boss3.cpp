#include "Boss3.h"
#include "ImprovedRifle.h"

Boss3::Boss3(Game * g, Player * player, Vector2D pos, BulletPool * pool) : Boss(g, player, Vector2D(pos.getX(), 200), pool, g->getTexture("EnemyMartyr")), Enemy(g, player, Vector2D(pos.getX(), 200), g->getTexture("EnemyMartyr"))
{
	_life = 250; // Demo Guerrilla
	_life1 = _life2 = _life3 = _life;

	delete(_myGun);
	_myGun = new ImprovedRifle(g);
	_myGun->setMaxCadence(0);
	_myGun->setBulletSpeed(8);
	_myGun->setDamage(3);

	_body->setW(12);
	_body->setH(26);

	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);

	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR | PLATFORMS);
	_body->getBody()->SetFixedRotation(true);
	_body->getBody()->SetGravityScale(0);


	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 3 / M_TO_PIXEL, b2Vec2(0, 3), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);

	_playerBody = _player->getComponent<BodyComponent>();

	_actualState = Shooting;
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
			_body->getBody()->SetLinearVelocity(b2Vec2(_velocity.getX() * _dir / M_TO_PIXEL, _body->getBody()->GetLinearVelocity().y));
	}
}


void Boss3::fase1(const double& deltaTime)
{
	if (!stop)
		circularShoot(deltaTime);
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
		_timeBeetwenBullets = 50;
		_doSomething = _game->random(1200, 1600);
		stop = true;
	}
	else
	{
		if (_actualBullet == 0)
		{
			_angle = -90;
			shootBullet();
		}
		else if (_timeOnShooting >= _timeBeetwenBullets)
		{
			shootBullet();
			_timeBeetwenBullets += 50;
		}
	}
}

void Boss3::shootBullet()
{
	shoot();
	_angle += _angleIncrease;
	_actualBullet++;

	if (_actualBullet == _numBullets)
	{
		_timeBeetwenBullets += 300;
		_num++;
		_actualBullet = 0;
	}
	
}

void Boss3::shoot()
{
	_myGun->enemyShoot(_myBulletPool, _bodyPos, _angle, "EnemyBullet");
}