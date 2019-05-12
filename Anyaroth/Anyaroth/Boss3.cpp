#include "Boss3.h"
#include "ImprovedRifle.h"
#include "SpawnerBoss.h"
#include "FloatingHead.h"
Boss3::Boss3(Game * g, Player * player, Vector2D pos, BulletPool * pool) : Boss(g, player, pos, pool, g->getTexture("EnemyMartyr")), Enemy(g, player, pos, g->getTexture("EnemyMartyr"))
{
	_life = 300; // Demo Guerrilla
	_life1 = _life;

	_name = "Angra Manyu";

	delete(_myGun);
	_myGun = new ImprovedRifle(g);
	_myGun->setMaxCadence(_rifleCadence);
	_myGun->setBulletSpeed(8);
	_myGun->setDamage(5);


	_gravGun = new GravityBombCannon(g);
	_gravGun->setMaxCadence(0);

	_otherGun = new BounceOrbCannon(g);
	_otherGun->setMaxCadence(0);
	_otherGun->setBulletSpeed(8);
	_otherGun->setDamage(10);


	_body->setW(12);
	_body->setH(26);

	_body->getBody()->SetGravityScale(_gravity);
	_body->getBody()->SetLinearDamping(_damping);

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

	_arm->setOffSet(Vector2D(30, 30));
	_armVision = true;

	_actualState = Moving;

	//activar al pasar a la fase 3
	_sensor = new BossSensor(g, this, { 100, 100 }, { 30, 30 });
	_sensor->setActive(false);
	addChild(_sensor);
	_invulnerable = true;

	_body->getBody()->SetActive(false);
	_armVision = false;

	addSensors();
}

void Boss3::setBoss3Panel(Boss3Panel * b)
{
	_boss3Panel = b;
	_boss3Panel->updateBossName(_name);

	//Actualizamos de primeras el aspecto del Panel del Jugador
	_boss3Panel->updateLifeBar(_life1.getLife(), _life.getLife());
	_boss3Panel->setVisible(false);
}

Boss3::~Boss3()
{ 
	delete _gravGun;
	delete _otherGun;
}

void Boss3::update(const double & deltaTime)
{
	if (_game->getCurrentState()->getCutScene() == nullptr)
	{
		DistanceEnemy::update(deltaTime);

		if (!isDead())
		{
			movement(deltaTime);

			if (_actualFase == Fase1)
				fase1(deltaTime);
			else if (_actualFase == Fase2)
				fase2(deltaTime);
			else if (_actualFase == Fase3)
				fase3(deltaTime);
			else
				beetwenFases(deltaTime);
		}
	}
}

void Boss3::movement(const double& deltaTime)
{
	if (_actualState == Moving)
	{
		_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
		_playerPos = Vector2D(_playerBody->getBody()->GetPosition().x * M_TO_PIXEL, _playerBody->getBody()->GetPosition().y * M_TO_PIXEL);

		double pos = _body->getBody()->GetPosition().x* M_TO_PIXEL;
		_dir = Vector2D((pos >= _playerPos.getX()) ? -1 : 1, _dir.getY());

		double range = _playerPos.getX() + _playerBody->getW() / 2 - _bodyPos.getX() + _body->getW() / 2;

		if (_dir.getX() == 1)
			_anim->unFlip();
		else
			_anim->flip();

		if (range <= -_stopRange || range >= _stopRange)
			_body->getBody()->SetLinearVelocity(b2Vec2(_velocity * _dir.getX() / M_TO_PIXEL, _body->getBody()->GetLinearVelocity().y));
	}
}

void Boss3::fase1(const double & deltaTime)
{
	_actualState = Idle;
	int aliveEnemies = 0;
	bool ok = true, HeadsDead = true;
	if (_initSpawn)
	{
		for(int i=0;i<_spawners.size();i++)
		{
			_spawners.at(i)->spawnEnemy();
		}
		_initSpawn = false;
	}
	else
	{
		if (!_headTurn)
		{
			for (int j = 0; j < _spawners.size(); j++)
			{
				aliveEnemies += _spawners.at(j)->aliveEnemies();
			}
			if (aliveEnemies == 0)
			{
				_headTurn = true;
				for (int x = 0; x < _heads.size(); x++)
				{
					_heads.at(x)->turnInvincibilityOff();
				}
			}
		}
		else
		{
			for (int x = 0; x < _heads.size(); x++)
			{

				ok = (_heads.at(x)->isInvincible() && ok);
				HeadsDead = (_heads.at(x)->isDead() && HeadsDead);
			}
			if (ok)
			{
				_headTurn = false;
				_initSpawn = true;
				if (HeadsDead)
				{
					_invulnerable = false;
					beetwenFases(deltaTime);
				}
			}
		}
	}
}

void Boss3::fase2(const double& deltaTime)
{
	if (_actualState == Shooting)
			circularShoot(deltaTime);
	else if (_actualState == GravAttack)
	{
		if (_noAction > _doSomething)
		{
			if (_game->random(0, 100) > 70)			
				_actualState = Shooting;
			else
			{
				_body->getBody()->SetActive(false);
				_arm->setActive(false);
				_anim->setVisible(false);
				_actualState = PortalAttack;
			}
			_noAction = 0;
		}
		else
			_noAction += deltaTime;
	}
	else if (_actualState == PortalAttack)
	{
		portalAttack(deltaTime);
	}
	else
	{
		if (_noAction > _doSomething)
		{
			int rand = _game->random(0, 100);
			if ( rand > 70)			
				_actualState = Shooting;			
			else if (rand > 45)
			{
				_body->getBody()->SetActive(false);
				_arm->setActive(false);
				_anim->setVisible(false);
				_actualState = PortalAttack;
			}
			else
			{
				shootGrav();
				_actualState = GravAttack;
			}
			_noAction = 0;
		}
		else
			_noAction += deltaTime;
	}
}

void Boss3::fase3(const double & deltaTime)
{
	checkDash(deltaTime);
	if (_actualState != Dashing)
	{
		if (_actualState != Shooting)
		{
			if (_noAction > _doSomething)
			{
				int rand = _game->random(0, 100);
				if (rand > 80 && _actualState != Jumping)
				{
					changeGun();
					_doSomething = _game->random(800, 1300);
				}
				else if (rand > 60)
				{
					_actualState = Shooting;
					_numBulletsRifle = _game->random(4, 8);
				}
				_noAction = 0;
			}
			else
				_noAction += deltaTime;
		}
		else
		{
			rifleShoot();
		}

		if (_bulletApproaching)
		{
			int rand = _game->random(0, 100);
			if (rand > 90)
			{
				_actualState = Dashing;
				dash();
			}
			else if (rand > 85 && _actualState != Jumping)
			{
				_actualState = Jumping;
				jump();
			}
			_bulletApproaching = false;
		}
	}
}

void Boss3::beetwenFases(const double& deltaTime)
{
	//if (_anim->animationFinished())
	//{
	if (_lastFase == Fase1)
	{
		changeFase(Fase2);
		_boss3Panel->setVisible(true);
		_body->getBody()->SetActive(true);
		_armVision = false;

		_actualState = PortalAttack;
		portalAttack(deltaTime);
	}
	else if (_lastFase == Fase2)
	{
		changeFase(Fase3);
		_sensor->setActive(true);
		_velocity = 100;
		_myGun->setMaxCadence(_rifleCadence);

		_life.setMaxLife(350);
		_life.resetLife();
		_life1.setMaxLife(350);
		_life1.resetLife();

		_boss3Panel->resetLifeBar(_life1.getLife(), _life.getLife());
		_name = "Angra Soldier";
		_boss3Panel->updateBossName(_name);//Provisional
		_actualState = Moving;
	}
	else
	{
		die();
	}
	_boss3Panel->updateLifeBar(_life1.getLife(), _life.getLife());
	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	//}
}

void Boss3::subLife(int damage)
{
	if (!_invulnerable)
	{
		if (!isDead() && !isbeetweenFases())
		{
			if (_life1.getLife() > 0)
			{
				manageLife(_life1, damage);
				_boss3Panel->updateLifeBar(_life1.getLife(), _life.getLife());
			}
		}
		_spawnParticles = true;
		_anim->hurt();
	}
}

void Boss3::portalAttack(const double& deltaTime)
{
	if (_timeOut > timeToReapear)
	{
		_body->getBody()->SetActive(true);
		_arm->setActive(true);
		_doSomething = _game->random(2000, 3000);
		_actualState = Moving;
		portalVisible = false;
		_timeOut = 0;

		b2Vec2 playerPos = _player->getComponent<BodyComponent>()->getBody()->GetPosition(), enemyPos = _body->getBody()->GetPosition();
		Vector2D playerDistance = Vector2D((playerPos.x - enemyPos.x)*M_TO_PIXEL, (playerPos.y - enemyPos.y)*M_TO_PIXEL);

		bool maxRange = _playerDistance.getX() < _explosionRange && _playerDistance.getX() > -_explosionRange && _playerDistance.getY() < _explosionRange && _playerDistance.getY() > -_explosionRange;

		if (maxRange)
		{
			bool midleRange = _playerDistance.getX() < _explosionRange / 2 && _playerDistance.getX() > -_explosionRange / 2 && _playerDistance.getY() < _explosionRange / 2 && _playerDistance.getY() > -_explosionRange / 2;

			if (playerDistance.getX() == 0)
			{
				_playerBody->getBody()->ApplyLinearImpulseToCenter(b2Vec2(_impulse * 10 * 3, _impulse * 10 * 2), true);
			}
			else if (midleRange)
				_playerBody->getBody()->ApplyLinearImpulseToCenter(b2Vec2(_impulse * _playerDistance.getX() * 3, _impulse * _playerDistance.getY() * 2), true);
			else
				_playerBody->getBody()->ApplyLinearImpulseToCenter(b2Vec2(_impulse * _playerDistance.getX(), _impulse * _playerDistance.getY()), true);

			_player->subLife(_explosionDamage);
		}
		_game->getCurrentState()->getMainCamera()->shake(2, 500);
	}
	else if (_timeOut > timeToShowPortal && !portalVisible)
	{
		_body->getBody()->SetTransform(b2Vec2((_playerBody->getBody()->GetPosition().x), _playerBody->getBody()->GetPosition().y), 0);
		_transform->setPosition(Vector2D(_playerBody->getBody()->GetPosition().x / M_TO_PIXEL, _playerBody->getBody()->GetPosition().y / M_TO_PIXEL));
		portalVisible = true;

		_anim->setVisible(true);
		//Se pone animacion del portal
	}
	else
		_timeOut += deltaTime;
}

void Boss3::circularShoot(const double& deltaTime)
{
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_timeOnShooting += deltaTime;
	_armVision = false;
	_myGun->setMaxCadence(0);

	if (_actualBullet == 0 && _num == 3)
	{
		_actualState = Moving;
		_armVision = true;
		_timeBeetwenBullets = 0;
		_doSomething = _game->random(1500, 3000);
		_num = 0;
		_timeOnShooting = 0;
		_myGun->setMaxCadence(_rifleCadence);
	}
	else
	{	
		if (_timeOnShooting >= _timeBeetwenBullets)		
			shootBullet(_numBullets, _angleIncrease);		
	}
}

void Boss3::changeGun()
{
	auto aux = _myGun;
	_myGun = _otherGun;
	_otherGun = aux;

	int numShots = _game->random(5, 10);
	double incrAngle = 180 / (numShots-1);
	shootBullet(numShots, incrAngle);

	_otherGun = _myGun;
	_myGun = aux;
}

void Boss3::dash()
{
	int dir = (_game->random(0, 2) == 0) ? -1 : 1;
	_body->getBody()->SetLinearVelocity(b2Vec2(-dir * _force, 0));

	_invulnerable = true;

	_body->getBody()->SetLinearDamping(0);
	_body->getBody()->SetGravityScale(0);
}

void Boss3::checkDash(double deltaTime)
{
	if (_actualState == Dashing)
	{
		_dashTimer -= deltaTime;
		if (_dashTimer <= 0)
		{
			_invulnerable = false;
			_dashTimer = _dashTime;
			_actualState = Moving;
			_body->getBody()->SetGravityScale(_gravity);
			_body->getBody()->SetLinearDamping(_damping);
		}
	}
}

void Boss3::jump()
{
	_body->getBody()->SetLinearVelocity(b2Vec2(_body->getBody()->GetLinearVelocity().x + _game->random(-75, 75), 0));
	_body->getBody()->ApplyLinearImpulse(b2Vec2(0 , -_jumpForce), _body->getBody()->GetWorldCenter(), true);
}

void Boss3::shootBullet(int numBullets, double angleIncrease)
{
	for (int i = 0; i < numBullets; i++)
	{
		shoot();
		_angle += angleIncrease;
		_actualBullet++;
	}

	_timeBeetwenBullets += _timeBeetwenCircularShoot;
	_num++;
	_actualBullet = 0;	
	_angle = 180;
}

void Boss3::shoot()
{
	_myGun->enemyShoot(_myBulletPool, _bodyPos, _angle, "EnemyBullet");
}

void Boss3::shootGrav()
{
	_arm->shoot();
	_gravGun->enemyShoot(_myBulletPool, _arm->getPosition(), !_anim->isFlipped() ? _arm->getAngle() + _game->random(-_fail, _fail) : _arm->getAngle() + 180 + _game->random(-_fail, _fail), "EnemyBullet");
	_doSomething = _game->random(800, 1500);
}

void Boss3::rifleShoot()
{
	if (_rifleBulletsCount >= _numBulletsRifle)
	{
		_actualState = Moving;
		_rifleBulletsCount = 0;
		_doSomething = _game->random(1000, 1500);
	}
	else
	{
		if (_myGun->canShoot())
		{
			_arm->shoot();
			_myGun->enemyShoot(_myBulletPool, _arm->getPosition(), !_anim->isFlipped() ? _arm->getAngle() + _game->random(-_fail, _fail) : _arm->getAngle() + 180 + _game->random(-_fail, _fail), "EnemyBullet");
			_rifleBulletsCount++;
		}
	}
}

void Boss3::beginCollision(GameObject * other, b2Contact* contact)
{
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	Boss::beginCollision(other, contact);
	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && (other->getTag() == "Ground" || other->getTag() == "Platform"))
	{
		_onFloor++;
		if (_onFloor <= 1 && _actualState == Jumping)
		{
			_actualState = Moving;
			_body->getBody()->SetLinearVelocity(b2Vec2(_velocity * _dir.getX() / M_TO_PIXEL, 0));
		}
		if (fA->GetFriction() == 26 || fB->GetFriction() == 26)
		{
			_body->getBody()->SetLinearVelocity(b2Vec2(0, _body->getBody()->GetLinearVelocity().y));
			_body->getBody()->ApplyLinearImpulse(b2Vec2(-10, 0), b2Vec2_zero, true);
		}
		else if (fA->GetFriction() == -26 || fB->GetFriction() == -26)
		{
			_body->getBody()->SetLinearVelocity(b2Vec2(0, _body->getBody()->GetLinearVelocity().y));
			_body->getBody()->ApplyLinearImpulse(b2Vec2(10, 0), b2Vec2_zero, true);
		}
	}
}
void Boss3::endCollision(GameObject * other, b2Contact* contact)
{
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && (other->getTag() == "Ground" || other->getTag() == "Platform"))
		_onFloor--;
}