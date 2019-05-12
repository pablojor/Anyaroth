#include "Boss3.h"
#include "ImprovedRifle.h"
#include "SpawnerBoss.h"
#include "FloatingHead.h"
Boss3::Boss3(Game * g, Player * player, Vector2D pos, BulletPool * pool) : Boss(g, player, pos, pool, g->getTexture("Angra")), Enemy(g, player, pos, g->getTexture("Angra"))
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

	_otherGun = new OrbShotgun(g);
	_otherGun->setMaxCadence(0);
	_otherGun->setBulletSpeed(8);
	_otherGun->setDamage(10);

	_arm->setTexture(_game->getTexture("AngraArmImproveRifle"));
	_arm->setOffSet(Vector2D(90, 105));
	_arm->getComponent<CustomAnimatedSpriteComponent>()->setVisible(false);

	_body->setW(80);
	_body->setH(170);
	_body->moveShape(b2Vec2(0, 3));
	_body->getBody()->SetGravityScale(_gravity);
	_body->getBody()->SetLinearDamping(_damping);

	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);

	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR | PLATFORMS);
	_body->getBody()->SetFixedRotation(true);


	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 3 / M_TO_PIXEL, b2Vec2(0, 8), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);

	_playerBody = _player->getComponent<BodyComponent>();

	_armVision = true;

	_actualState = Moving;

	_anim->addAnim(AnimatedSpriteComponent::AngraIdle, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraWalk, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraBH, 18, false);
	_anim->addAnim(AnimatedSpriteComponent::AngraAppear, 21, false);
	_anim->addAnim(AnimatedSpriteComponent::AngraDisappear, 15, false);
	_anim->addAnim(AnimatedSpriteComponent::AngraRing, 13, false);
	_anim->addAnim(AnimatedSpriteComponent::AngraDie, 34, false);

	_anim->playAnim(AnimatedSpriteComponent::AngraIdle);
	_anim->setVisible(false);

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

	if (isDead() || _player->isDead())
		_boss3Panel->setVisible(false);
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
		{
			_anim->unFlip();
			_arm->setOffSet(Vector2D(245, 105));
		}
		else
		{
			_anim->flip();
			_arm->setOffSet(Vector2D(90, 105));
		}

		if (range <= -_stopRange || range >= _stopRange && _actualState != Shooting)
		{
			_body->getBody()->SetLinearVelocity(b2Vec2(_velocity * _dir.getX() / M_TO_PIXEL, _body->getBody()->GetLinearVelocity().y));
			_anim->playAnim(AnimatedSpriteComponent::AngraWalk);
		}
		else if(_actualState != PortalAttack && _actualState != Shooting)
		{
			_anim->playAnim(AnimatedSpriteComponent::AngraIdle);
		}
	}
}

void Boss3::fase1(const double & deltaTime)
{
	_actualState = Idle;
	int aliveEnemies = 0;
	bool ok = true, HeadsDead = true;
	if (_initSpawn)
	{
		for (int i = 0; i < _spawners.size(); i++)
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
					_initSpawn = false;
					_headTurn = true;
					beetwenFases(deltaTime);
					_throneAnim->playAnim(AnimatedSpriteComponent::ThroneEnd);
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
		if(_anim->getCurrentAnim() == AnimatedSpriteComponent::AngraBH && _anim->animationFinished())
		{
			if (_game->random(0, 100) > 60)
			{
				_actualState = Shooting;
				_anim->playAnim(AnimatedSpriteComponent::AngraRing);
			}
			else
			{
				_anim->playAnim(AnimatedSpriteComponent::AngraDisappear);
				_actualState = PortalAttack;
			}
			_alreadyShoot = false;
		}
		else if (!_alreadyShoot)
		{
			if (_timeWaiting > _timeToShoot)
			{
				_timeWaiting = 0;
				shootGrav();
				_alreadyShoot = true;
			}
			else
				_timeWaiting += deltaTime;
		}
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
			if (rand > 60)
			{
				_actualState = Shooting;
				_anim->playAnim(AnimatedSpriteComponent::AngraRing);
			}
			else if (rand > 40)
			{
				_actualState = PortalAttack;
				_anim->playAnim(AnimatedSpriteComponent::AngraDisappear);
			}
			else
			{
				_anim->playAnim(AnimatedSpriteComponent::AngraBH);
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
		if (_throneAnim->animationFinished())
		{
			changeFase(Fase2);
			_boss3Panel->setVisible(true);
			_body->getBody()->SetActive(true);
			_armVision = false;

			_actualState = PortalAttack;
			_anim->playAnim(AnimatedSpriteComponent::AngraDisappear);
			portalAttack(deltaTime);
		}
	}
	else if (_lastFase == Fase2)
	{
		changeFase(Fase3);
		_sensor = new BossSensor(_game, this, { 100, 100 }, { 30, 30 });
		addChild(_sensor);
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
		_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
		_corpse = new BossCorpse(_game, _transform->getPosition(), _game->getTexture("PistolIcon"));
		addChild(_corpse);
	}
	else
	{
		die();
	}
	_boss3Panel->updateLifeBar(_life1.getLife(), _life.getLife());
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
				_throneAnim->playAnim(AnimatedSpriteComponent::ThroneEnd);
			}
		}
		_spawnParticles = true;
		_anim->hurt();
	}
}

void Boss3::portalAttack(const double& deltaTime)
{
	if (_anim->getCurrentAnim() == AnimatedSpriteComponent::AngraDisappear && _anim->animationFinished())
	{
		_body->getBody()->SetActive(false);
		_arm->setActive(false);
		_anim->setVisible(false);
		realGone = true;
	}
	if (realGone)
	{
		if (_timeOut > timeToReapear)
		{
			_body->getBody()->SetActive(true);
			_arm->setActive(true);
			_anim->setVisible(true);
			_doSomething = _game->random(2000, 3000);
			_actualState = Moving;
			portalVisible = false;
			_timeOut = 0;
			realGone = false;

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
			_body->getBody()->SetTransform(b2Vec2((_playerBody->getBody()->GetPosition().x), _playerBody->getBody()->GetPosition().y - _body->getH()/2 - _playerBody->getH() -5), 0);
			_transform->setPosition(Vector2D(_playerBody->getBody()->GetPosition().x / M_TO_PIXEL, _playerBody->getBody()->GetPosition().y / M_TO_PIXEL));
			portalVisible = true;

			_anim->setVisible(true);
			_anim->playAnim(AnimatedSpriteComponent::AngraAppear);
		}
		else
			_timeOut += deltaTime;
	}
}

void Boss3::circularShoot(const double& deltaTime)
{
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_armVision = false;
	_myGun->setMaxCadence(0);

	if (_num == 3 && _anim->getCurrentAnim() == AnimatedSpriteComponent::AngraRing && _anim->animationFinished())
	{
		_actualState = Moving;
		_armVision = true;
		_timeBeetwenBullets = 0;
		_doSomething = _game->random(1500, 3000);
		_num = 0;
		_timeOnShooting = 0;
		_myGun->setMaxCadence(_rifleCadence);
		_needToFinishAnim = false;
	}
	else if(_num != 3)
	{
		if (!_needToFinishAnim)
		{
			if (_timeOnShooting >= _timeBeetwenBullets)
			{
				shootBullet(_numBullets, _angleIncrease);
				_needToFinishAnim = true;
			}
			else
			{
				_timeOnShooting += deltaTime;
			}
		}
		else
		{
			if (_anim->getCurrentAnim() == AnimatedSpriteComponent::AngraRing && _anim->animationFinished())
			{
				_anim->playAnim(AnimatedSpriteComponent::AngraIdle);
				_anim->playAnim(AnimatedSpriteComponent::AngraRing);
				_needToFinishAnim = false;
			}
		}
	}
}

void Boss3::AngraSoldierSpawn()
{
	_anim->setTexture(_game->getTexture("AngraSoldier"));
	_anim->reset();
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierIdle, 16, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierWalk, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierWalkBack, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierBeforeJump, 1, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierJump, 4, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierStartFalling, 2, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierFalling, 2, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierDash, 5, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierDashDown, 3, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierDashBack, 5, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierDie, 35, true);
	
	_body->setW(12);
	_body->setH(26);
	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);

	_arm->setTexture(_game->getTexture("AngraArmImproveRifle"));
	_arm->setActive(true);
}

void Boss3::changeGun()
{
	auto aux = _myGun;
	_myGun = _otherGun;
	_otherGun = aux;

	shoot();

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
	_body->getBody()->ApplyLinearImpulse(b2Vec2(0, -_jumpForce), _body->getBody()->GetWorldCenter(), true);
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
	_myGun->enemyShoot(_myBulletPool,Vector2D( _bodyPos.getX(), _bodyPos.getY() - 10), _angle, "EnemyBullet");
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

BossCorpse::BossCorpse(Game * g, Vector2D pos, Texture* texture): GameObject(g)
{
	TransformComponent* t = addComponent<TransformComponent>();
	t->setPosition(pos);

	addComponent<Texture>(texture);

	_sprite = addComponent<SpriteComponent>();
}
