#include "Boss3.h"
#include "ImprovedRifle.h"
#include "SpawnerBoss.h"
#include "FloatingHead.h"
#include "CutScene.h"

Boss3::Boss3(Game * g, Player * player, Vector2D pos, BulletPool * pool) : Boss(g, player, pos, pool, g->getTexture("Angra")), Enemy(g, player, pos, g->getTexture("Angra"), "die2", "boss1Hit", "meleeEnemyHit")
{
	_life = 600;
	_life1 = _life;

	_name = "Angra Manyu";

	delete(_myGun);
	_myGun = new ImprovedRifle(g);
	_myGun->setMaxCadence(_rifleCadence);
	_myGun->setBulletSpeed(15);
	_myGun->setDamage(6);

	_gravGun = new GravityBombCannon(g);
	_gravGun->setMaxCadence(0);

	_otherGun = new OrbShotgun(g);
	_otherGun->setMaxCadence(1000);
	_otherGun->setBulletSpeed(20);
	_otherGun->setDamage(8);

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
	_anim->addAnim(AnimatedSpriteComponent::AngraDie1, 21, false);
	_anim->addAnim(AnimatedSpriteComponent::AngraDie2, 13, false);

	_anim->playAnim(AnimatedSpriteComponent::AngraIdle);
	_anim->setVisible(false);

	_invulnerable = true;

	_body->getBody()->SetActive(false);
	_armVision = false;

	addSensors();
}

void Boss3::handleAnimations(double time)
{
	if (_actualFase == Fase2)
	{
		if (_throneAnim->getCurrentAnim() == AnimatedSpriteComponent::ThroneEnd1 && _throneAnim->animationFinished())
		{
			_throneAnim->playAnim(AnimatedSpriteComponent::ThroneEnd2);
			_alreadyDead = true;
		}
	}
	else if(_actualFase == BetweenFase)
	{
		if (_anim->getCurrentAnim() == AnimatedSpriteComponent::AngraDie1 && _anim->animationFinished())
			_anim->playAnim(AnimatedSpriteComponent::AngraDie2);
	}
	else if (_actualFase == Fase3)
	{
		if (_actualState != Dashing)
		{
			if (_actualState != Moving)
			{
				auto vel = _body->getBody()->GetLinearVelocity();

				if (vel.y > 2)
					_anim->playAnim(AnimatedSpriteComponent::AngraSoldierFalling);
				else if (vel.y < 2 && vel.y > -2)
					_anim->playAnim(AnimatedSpriteComponent::AngraSoldierStartFalling);
				else if (vel.y < -2)
					_anim->playAnim(AnimatedSpriteComponent::AngraSoldierJump);
			}

			_playerPos = Vector2D(_playerBody->getBody()->GetPosition().x * M_TO_PIXEL, _playerBody->getBody()->GetPosition().y * M_TO_PIXEL);
			double pos = _body->getBody()->GetPosition().x* M_TO_PIXEL;
			_dir = Vector2D((pos >= _playerPos.getX()) ? -1 : 1, _dir.getY());

			if (_dir.getX() == 1)
				_anim->unFlip();
			else
				_anim->flip();
		}
	}
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
	_myBulletPool->stopBullets();
	delete _gravGun;
	delete _otherGun;
}

void Boss3::update(double deltaTime)
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

			handleAnimations(deltaTime);
		}
		else if (!_finishLevel)
		{
			CutScene* cutscene = new CutScene(_player);
			cutscene->addWaitEvent(1000);
			_game->getSoundManager()->stopMusic();
			cutscene->addDialogueEvent(_game->getCurrentState()->getPlayHUD()->getDialoguePanel(), _game->getDialogue("Angra Manyu 2"));
			cutscene->addWaitEvent(1000);
			cutscene->addChangeLevelEvent();
			_game->getCurrentState()->addCutScene(cutscene);
			cutscene->play();

			_finishLevel = true;
		}

		if (isDead() || _player->isDead())
			_boss3Panel->setVisible(false);
	}
}

void Boss3::movement(double deltaTime)
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

			if (_actualFase == Fase2)
				_arm->setOffSet(Vector2D(245, 105));
		}
		else
		{
			_anim->flip();

			if (_actualFase == Fase2)
				_arm->setOffSet(Vector2D(90, 105));
		}

		if (range <= -_stopRange || range >= _stopRange && _actualState != Shooting)
		{
			_body->getBody()->SetLinearVelocity(b2Vec2(_velocity * _dir.getX() / M_TO_PIXEL, _body->getBody()->GetLinearVelocity().y));
			_anim->playAnim(AnimatedSpriteComponent::AngraWalk);
		}
		else if (_actualState != PortalAttack && _actualState != Shooting)
		{
			_anim->playAnim(AnimatedSpriteComponent::AngraIdle);
		}
	}
}

void Boss3::fase1(double deltaTime)
{
	_actualState = Idle;
	int aliveEnemies = 0;
	bool ok = true, HeadsDead = true;

	if (_initSpawn)
	{
		for (int i = 0; i < _spawners.size(); i++)
			_spawners.at(i)->spawnEnemy();

		_initSpawn = false;
	}
	else
	{
		if (!_headTurn)
		{
			for (int j = 0; j < _spawners.size(); j++)
				aliveEnemies += _spawners.at(j)->aliveEnemies();

			if (aliveEnemies == 0)
			{
				_headTurn = true;

				for (int x = 0; x < _heads.size(); x++)
					if(!_heads[x]->isDead())
						_heads.at(x)->turnInvincibilityOff();
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

					if (!_alreadyDead)
					{
						_throneAnim->playAnim(AnimatedSpriteComponent::ThroneEnd1);
						_game->getSoundManager()->playSFX("boss3Teleport");
					}
				}
			}
		}
	}
}

void Boss3::fase2(double deltaTime)
{
	if (_actualState == Shooting)
		circularShoot(deltaTime);
	else if (_actualState == GravAttack)
	{
		if (_anim->getCurrentAnim() == AnimatedSpriteComponent::AngraBH && _anim->animationFinished())
		{
			if (_game->random(0, 100) < 25)
			{
				_actualState = Shooting;
				_anim->playAnim(AnimatedSpriteComponent::AngraRing);
			}
			else
			{
				_anim->playAnim(AnimatedSpriteComponent::AngraDisappear);
				_actualState = PortalAttack;
				_game->getSoundManager()->playSFX("boss3Teleport");
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
			int random = _game->random(0, 100);

			if (random < 40)
			{
				_actualState = Shooting;
				_anim->playAnim(AnimatedSpriteComponent::AngraRing);
			}
			else if (random < 60)
			{
				_actualState = PortalAttack;
				_anim->playAnim(AnimatedSpriteComponent::AngraDisappear);
				_game->getSoundManager()->playSFX("boss3Teleport");
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

void Boss3::fase3(double deltaTime)
{
	checkDash(deltaTime);

	if (_actualState != Dashing)
	{
		if (_actualState != Shooting)
		{
			if (_noAction > _doSomething)
			{
				int random = _game->random(0, 100);

				if (random < 40 && _actualState != Jumping)
				{
					changeGun();
					_doSomething = _game->random(800, 1300);
				}
				else if (random < 80)
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
			int random = _game->random(0, 100);

			if (random < 20)
			{
				_actualState = Dashing;
				dash();
			}
			else if (random < 40 && _actualState != Jumping)
			{
				_actualState = Jumping;
				jump();
			}
			_bulletApproaching = false;
		}
	}
}

void Boss3::beetwenFases(double deltaTime)
{
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
		if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::AngraDie2)
		{
			changeFase(Fase3);
			_sensor = new BossSensor(_game, this, { 100, 100 }, { 30, 30 });
			addChild(_sensor);
			_velocity = 100;
			_myGun->setMaxCadence(_rifleCadence);

			_life.setMaxLife(200);
			_life.resetLife();
			_life1.setMaxLife(200);
			_life1.resetLife();

			_boss3Panel->resetLifeBar(_life1.getLife(), _life.getLife());
			_name = "Angra Soldier";
			_boss3Panel->updateBossName(_name);//Provisional
			_actualState = Jumping;

			double pos = _body->getBody()->GetPosition().x* M_TO_PIXEL;
			_dir = Vector2D((pos >= _playerPos.getX()) ? -1 : 1, _dir.getY());

			_corpse->setActive(true);
			bool flip;
			if (_dir.getX() == 1)
				_corpse->getComponent<SpriteComponent>()->unFlip();
			else
				_corpse->getComponent<SpriteComponent>()->flip();

			_corpse->getComponent<TransformComponent>()->setPosition(_transform->getPosition());
			AngraSoldierSpawn();
		}
	}
	else
		die();

	_boss3Panel->updateLifeBar(_life1.getLife(), _life.getLife());
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
			if (_life1.getLife() <= 0 && _lastFase == Fase2)
			{
				_anim->playAnim(AnimatedSpriteComponent::AngraDie1);
				_actualState = -1;
			}
			if (_actualFase == Fase3)
				_arm->hurt();
		}
		_spawnParticles = true;
		_anim->hurt();
	}
}

void Boss3::portalAttack(double deltaTime)
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
			_game->getSoundManager()->playSFX("martyrExplosion");
		}
		else if (_timeOut > timeToShowPortal && !portalVisible)
		{
			_body->getBody()->SetTransform(b2Vec2((_playerBody->getBody()->GetPosition().x), _playerBody->getBody()->GetPosition().y - _body->getH() / 2 - _playerBody->getH() - 5), 0);
			_transform->setPosition(Vector2D(_playerBody->getBody()->GetPosition().x / M_TO_PIXEL, _playerBody->getBody()->GetPosition().y / M_TO_PIXEL));
			portalVisible = true;

			_anim->setVisible(true);
			_anim->playAnim(AnimatedSpriteComponent::AngraAppear);
		}
		else
			_timeOut += deltaTime;
	}
}

void Boss3::circularShoot(double deltaTime)
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
	else if (_num != 3)
	{
		if (!_needToFinishAnim)
		{
			if (_timeOnShooting >= _timeBeetwenBullets)
			{
				shootBullet(_numBullets, _angleIncrease);
				_needToFinishAnim = true;
			}
			else
				_timeOnShooting += deltaTime;
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
	deleteComponent<Texture>(_texture);
	_texture = _game->getTexture("AngraSoldier");
	addComponent<Texture>(_texture);
	_anim->setTexture(_game->getTexture("AngraSoldier"));

	_anim->reset();
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierIdle, 16, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierWalk, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierWalkBack, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierBeforeJump, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierJump, 4, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierStartFalling, 2, false);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierFalling, 2, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierDash, 5, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierDashDown, 3, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierDashBack, 5, true);
	_anim->addAnim(AnimatedSpriteComponent::AngraSoldierDie, 35, false);

	b2Vec2 lastPos = _body->getBody()->GetPosition();
	_body->deleteBody();
	deleteComponent<BodyComponent>(_body);
	delPhysicsComponent(_body);
	delete _body;

	_body = addComponent<BodyComponent>();

	_body->setW(12);
	_body->setH(26);

	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetType(b2_dynamicBody);

	_body->getBody()->SetLinearDamping(3);
	_body->getBody()->SetGravityScale(8);

	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR | PLATFORMS);
	_body->getBody()->SetFixedRotation(true);

	_body->getBody()->SetTransform(lastPos, 0);

	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 3 / M_TO_PIXEL, b2Vec2(0, 3), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);

	_myGun->setArmTexture(_game->getTexture("AngraArmImprovedRifle"));
	_arm->setTexture(_game->getTexture("AngraArmImprovedRifle"));
	_arm->setActive(true);
	_arm->getComponent<CustomAnimatedSpriteComponent>()->setVisible(true);
	_arm->setOffSet(Vector2D(28, 15));
}

void Boss3::changeGun()
{
	auto aux = _myGun;
	_myGun = _otherGun;
	_otherGun = aux;
	_arm->setTexture(_myGun->getArmTexture());
}

void Boss3::dash()
{
	int dir = (_game->random(0, 2) == 0) ? -1 : 1;
	_body->getBody()->SetLinearVelocity(b2Vec2(-dir * _force, 0));

	//Si la direccion en la que se mueve es iguall a la direccion en la que hace el dash, es hacia el delante
	if (dir *_dir.getX() == 1)
		_anim->playAnim(AnimatedSpriteComponent::AngraSoldierDashBack);
	else
		_anim->playAnim(AnimatedSpriteComponent::AngraSoldierDash);

	_invulnerable = true;

	_body->getBody()->SetLinearDamping(0);
	_body->getBody()->SetGravityScale(0);
	_game->getSoundManager()->playSFX("dash");
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
			_body->getBody()->SetGravityScale(_gravity);
			_body->getBody()->SetLinearDamping(_damping);

			if (_onFloor == 0)
				_actualState = Jumping;
			else
				_actualState = Moving;
		}
	}
}

void Boss3::jump()
{
	_anim->playAnim(AnimatedSpriteComponent::AngraSoldierBeforeJump);
	_body->getBody()->SetLinearVelocity(b2Vec2(_body->getBody()->GetLinearVelocity().x + _game->random(-75, 75), 0));
	_body->getBody()->ApplyLinearImpulse(b2Vec2(0, -_jumpForce), _body->getBody()->GetWorldCenter(), true);
	_game->getSoundManager()->playSFX("jump");
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
	_myGun->enemyShoot(_myBulletPool, Vector2D(_bodyPos.getX(), _bodyPos.getY() - 10), _angle, "EnemyBullet");
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
			_anim->playAnim(AnimatedSpriteComponent::AngraSoldierIdle);
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

void Boss3::die()
{
	_anim->die();
	_anim->playAnim(AnimatedSpriteComponent::AngraSoldierDie);

	setDead(true);
	_body->filterCollisions(DEAD_ENEMIES, FLOOR | PLATFORMS);

	_game->getSoundManager()->playSFX(_deathSound);
	_arm->setActive(false);
}

BossCorpse::BossCorpse(Game * g, Vector2D pos, Texture* texture) : GameObject(g)
{
	TransformComponent* t = addComponent<TransformComponent>();
	t->setPosition(pos);

	addComponent<Texture>(texture);

	_sprite = addComponent<SpriteComponent>();
}