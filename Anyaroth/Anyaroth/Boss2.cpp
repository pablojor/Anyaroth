#include "Boss2.h"
#include "Poleaxe.h"
#include "ImprovedShotgun.h"

Boss2::Boss2(Game* g, Player* player, Vector2D pos, BulletPool* pool) : Boss(g, player, pos, pool, g->getTexture("Azura")), Enemy(g, player, pos, g->getTexture("Azura"))
{
	_life = 20; // Demo Guerrilla
	_life1 = _life2 = _life3 = _life;

	_myGun = new ImprovedShotgun(g);
	_myGun->setBulletSpeed(60);

	_arm->setOffSet(Vector2D(140, 105));
	_arm->getComponent<CustomAnimatedSpriteComponent>()->setVisible(false);

	_anim->addAnim(AnimatedSpriteComponent::AzuraSpinEnd1, 5, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraSpinEnd2, 5, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraSpinEnd3, 5, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraSpinLoop1, 2, true);
	_anim->addAnim(AnimatedSpriteComponent::AzuraSpinLoop2, 2, true);
	_anim->addAnim(AnimatedSpriteComponent::AzuraSpinLoop3, 2, true);
	_anim->addAnim(AnimatedSpriteComponent::AzuraIdle1, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::AzuraIdle2, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::AzuraIdle3, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::AzuraWalk1, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::AzuraWalk2, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::AzuraWalk3, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::AzuraCannon1, 23, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraCannon2, 23, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraCannon3, 23, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraJump, 23, false, 85);
	_anim->addAnim(AnimatedSpriteComponent::AzuraSpinStart1, 10, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraSpinStart2, 10, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraSpinStart3, 10, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraScream1to2, 17, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraScream2to3, 17, false);
	_anim->addAnim(AnimatedSpriteComponent::AzuraDie, 20, false);

	_anim->playAnim(AnimatedSpriteComponent::AzuraIdle1);
	
	_body->setW(40);
	_body->setH(100);

	_body->moveShape(b2Vec2(0, 2));

	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);

	_body->addCricleShape(b2Vec2(0, 6.5), 2, PLAYER, FLOOR | PLATFORMS);
	_body->getBody()->SetFixedRotation(true);
	_body->getBody()->SetGravityScale(10);

	_originalPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	
	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 3 / M_TO_PIXEL, b2Vec2(0, 9.5), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);

	_armVision = true;

	_playerBody = _player->getComponent<BodyComponent>();

	_lasers = new LaserHandler(g, g->getTexture("Arm"), g->getTexture("ArmUp"), player, 8);
	addChild(_lasers);

	_melee = new Poleaxe(getGame(), { 115,15 }, PLAYER, 2, 40, 75, this);
	addChild(_melee);
}


Boss2::~Boss2()
{
}

void Boss2::Jump()
{
	_body->getBody()->ApplyLinearImpulseToCenter(b2Vec2(_dir * 5000, -6000), true);

	b2PolygonShape shape;
	shape.SetAsBox(35 / M_TO_PIXEL, 25 / M_TO_PIXEL, b2Vec2(0, 5), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = MELEE;
	fDef.filter.maskBits = PLAYER;
	fDef.isSensor = true;
	setTag("Melee");
	_body->addFixture(&fDef, this);
	
	_damage = 20;
}


void Boss2::movement(const double& deltaTime)
{
	if (_actualFase != BetweenFase)
	{
		if (_endJump)
			endJump();
		_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
		_playerPos = Vector2D(_playerBody->getBody()->GetPosition().x * M_TO_PIXEL, _playerBody->getBody()->GetPosition().y * M_TO_PIXEL);

		double pos = _body->getBody()->GetPosition().x* M_TO_PIXEL;
		_dir = (pos >= _playerPos.getX()) ? -1 : 1;

		double range = _playerPos.getX() + _playerBody->getW() / 2 - _bodyPos.getX() +_body->getW() / 2;


		if (_dir == 1)
			_anim->unFlip();
		else
			_anim->flip();

		if (_actualState != Jumping && (range <= -_stopRange || range >= _stopRange) && _actualState == Moving || _actualState == Meleeing)
		{
			_body->getBody()->SetLinearVelocity(b2Vec2(_velocity.getX() * _dir / M_TO_PIXEL, _body->getBody()->GetLinearVelocity().y));
			
			auto anim = _anim->getCurrentAnim();
			if (anim != AnimatedSpriteComponent::AzuraCannon1 && anim != AnimatedSpriteComponent::AzuraCannon2 && anim != AnimatedSpriteComponent::AzuraCannon3 && _actualState == Moving)
			{
				if (_life1.getLife() > 0)
					_anim->playAnim(AnimatedSpriteComponent::AzuraWalk1);
				else if (_life2.getLife() > 0)
					_anim->playAnim(AnimatedSpriteComponent::AzuraWalk2);
				else
					_anim->playAnim(AnimatedSpriteComponent::AzuraWalk3);
			}
		}
		else if(_actualState != Jumping)
		{
			_body->getBody()->SetLinearVelocity(b2Vec2(0, _body->getBody()->GetLinearVelocity().y));

			auto anim = _anim->getCurrentAnim();
			if (anim != AnimatedSpriteComponent::AzuraCannon1 && anim != AnimatedSpriteComponent::AzuraCannon2 && anim != AnimatedSpriteComponent::AzuraCannon3)
			{
				if (_life1.getLife() > 0)
					_anim->playAnim(AnimatedSpriteComponent::AzuraIdle1);
				else if (_life2.getLife() > 0)
					_anim->playAnim(AnimatedSpriteComponent::AzuraIdle2);
				else
					_anim->playAnim(AnimatedSpriteComponent::AzuraIdle3);
			}
		}
	}
}

void Boss2::beginCollision(GameObject * other, b2Contact* contact)
{
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	Boss::beginCollision(other, contact);
	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && (other->getTag() == "Ground" || other->getTag() == "Platform"))
	{
		
			_onFloor ++;
			if (_onFloor <= 1)
			{
				if (_actualState == Jumping)
					_endJump = true;
				setTag("Enemy");
				_actualState = Moving;
			}
		
	}
}


void Boss2::endCollision(GameObject * other, b2Contact* contact)
{
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && (other->getTag() == "Ground" || other->getTag() == "Platform"))
		 _onFloor --;
}

void Boss2::meleeAttack()
{
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	int dir = (_bodyPos.getX() >= _playerPos.getX()) ? -1 : 1;
	_melee->meleeAttack(_bodyPos.getX(), _bodyPos.getY(), dir);

	_melee->setActive(false);

	//if (_life1.getLife() > 0)
	//	//_anim->playAnim(AnimatedSpriteComponent::AzuraSpin1);
	//else if (_life2.getLife() > 0)
	//	//_anim->playAnim(AnimatedSpriteComponent::AzuraSpin2);
	//else
	//	//_anim->playAnim(AnimatedSpriteComponent::AzuraSpin3);

	_velocity = { _velocity.getX() + _speedIncrement, _velocity.getY() };
}

void Boss2::endJump()
{
	_endJump = false;
	_jump = false;
	_body->getBody()->DestroyFixture(_body->getBody()->GetFixtureList());
	_player->stunPlayer();
	_doSomething = _game->random(800, 1500);
}

void Boss2::checkMelee(const double& deltaTime)
{
	if (_melee != nullptr)
	{
		if (_anim->animationFinished())
		{
			_armVision = true;
			_velocity = { _originalVelocity.getX(), _originalVelocity.getY() };
			_doSomething = _game->random(400, 800);
			_actualState = Moving;
			_melee->endMelee();
			_timeOnMelee = 0;
		}
		else
		{
			if (_timeOnMelee > _timeStartMelee)
			{
				_melee->setActive(true);
			}
			else
				_timeOnMelee += deltaTime;
		}

	}
}

void Boss2::fase1(const double& deltaTime)
{
	if (_actualState != Shooting)
	{
		if (_actualState != Meleeing)
		{
			if (_noAction > _doSomething)
			{
				if (_playerPos.distance(_bodyPos) <= _shootRange)
				{
					_actualState = Shooting;
					_noAction = 0;
				}

				else
				{
					meleeAttack();
					_actualState = Meleeing;
					_noAction = 0;
					_armVision = false;
				}
			}
			else
				_noAction += deltaTime;
		}
		else
			checkMelee(deltaTime);
	}
	else
	{
		auto anim = _anim->getCurrentAnim();
		if ((anim == AnimatedSpriteComponent::AzuraCannon1 || anim != AnimatedSpriteComponent::AzuraCannon2 || anim != AnimatedSpriteComponent::AzuraCannon3) && _anim->animationFinished())
		{
			_actualState = Moving;
			if (_life1.getLife() > 0)
				_anim->playAnim(AnimatedSpriteComponent::AzuraIdle1);
			else if (_life2.getLife() > 0)
				_anim->playAnim(AnimatedSpriteComponent::AzuraIdle2);
			else
				_anim->playAnim(AnimatedSpriteComponent::AzuraIdle3);
			_timeWaiting = 0;
		}
		else
		{
			if (_life1.getLife() > 0)
				_anim->playAnim(AnimatedSpriteComponent::AzuraCannon1);
			else if (_life2.getLife() > 0)
				_anim->playAnim(AnimatedSpriteComponent::AzuraCannon2);
			else
				_anim->playAnim(AnimatedSpriteComponent::AzuraCannon3);
		}
		if (_timeWaiting > _timeToShoot)
		{
			shoot();
			_timeWaiting = 0;
		}
		else
			_timeWaiting += deltaTime;

	}
}

void Boss2::fase2(const double& deltaTime)
{
	fase1(deltaTime);
}

void Boss2::fase3(const double& deltaTime)
{
	if (_actualState != Jumping)
	{
		if (_actualState != Shooting)
		{
			if (_actualState != Meleeing)
			{
				if (_noAction > _doSomething)
				{
					int ra = _game->random(0, 100);
					if (ra >= 70)
					{
						_actualState = Jumping;
						_noAction = 0;
						_anim->playAnim(AnimatedSpriteComponent::AzuraJump);
					}
					else
						fase2(deltaTime);
				}
				else
					_noAction += deltaTime;
			}
			else
				checkMelee(deltaTime);
		}
		else
		{
			auto anim = _anim->getCurrentAnim();
			if ((anim == AnimatedSpriteComponent::AzuraCannon1 || anim != AnimatedSpriteComponent::AzuraCannon2 || anim != AnimatedSpriteComponent::AzuraCannon3) && _anim->animationFinished())
			{
				_actualState = Moving;
				if (_life1.getLife() > 0)
					_anim->playAnim(AnimatedSpriteComponent::AzuraIdle1);
				else if (_life2.getLife() > 0)
					_anim->playAnim(AnimatedSpriteComponent::AzuraIdle2);
				else
					_anim->playAnim(AnimatedSpriteComponent::AzuraIdle3);
				_timeWaiting = 0;
			}
			else
			{
				if (_life1.getLife() > 0)
					_anim->playAnim(AnimatedSpriteComponent::AzuraCannon1);
				else if (_life2.getLife() > 0)
					_anim->playAnim(AnimatedSpriteComponent::AzuraCannon2);
				else
					_anim->playAnim(AnimatedSpriteComponent::AzuraCannon3);
			}
			if (_timeWaiting > _timeToShoot)
			{
				shoot();
				_timeWaiting = 0;
			}
			else
				_timeWaiting += deltaTime;

		}
	}
	else
	{
		checkJump(deltaTime);
	}

}

void Boss2::checkJump(const double& deltaTime)
{
	if (!_jump)
	{
		if (_timeWaitingJump > _timeToJump && !_jump)
		{
			Jump();
			_jump = true;
			_timeWaitingJump = 0;
		}
		else
			_timeWaitingJump += deltaTime;
	}
}

void Boss2::beetwenFases(const double& deltaTime)
{
	if (_anim->animationFinished() || _life3.getLife() == 0)
	{
		_originalVelocity = _originalVelocity + Vector2D(_speedIncrement, 0);
		_velocity = _originalVelocity;
		if (_lastFase == Fase1)
		{
			_lasers->Activate();
			changeFase(Fase2);
		}
		else if (_lastFase == Fase2)
			changeFase(Fase3);
		else
		{
			die();
			_lasers->Deactivate();
		}
		_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
		_actualState = Moving;
		if (_life1.getLife() > 0)
			_anim->playAnim(AnimatedSpriteComponent::AzuraIdle1);
		else if (_life2.getLife() > 0)
			_anim->playAnim(AnimatedSpriteComponent::AzuraIdle2);
		else if (_life3.getLife() > 0)
			_anim->playAnim(AnimatedSpriteComponent::AzuraIdle3);

		_particles = false;
	}
	else
	{
		if (_melee != nullptr && _melee->isActive())
		{
			_melee->endMelee();
			_velocity = { _originalVelocity.getX(), _originalVelocity.getY() };
			_timeOnMelee = 0;
		}
		if (!_body->getBody()->GetWorld()->IsLocked() && !_particles)
		{
			if (_life2.getLife() > 0)
			{
				ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("AzuraParticle1"), 1, Vector2D(_bodyPos.getX() + _game->random(-20,20), _bodyPos.getY() + _game->random(-10, 10)), 5, _game->random(0, 360), 2000, 1);
				ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("AzuraParticle2"), 1, Vector2D(_bodyPos.getX() + _game->random(-20, 20), _bodyPos.getY() + _game->random(-10, 10)), 5, _game->random(0, 360), 2000, 1);
				ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("AzuraParticle3"), 1, Vector2D(_bodyPos.getX() + _game->random(-20, 20), _bodyPos.getY() + _game->random(-10, 10)), 5, _game->random(0, 360), 2000, 1);
				ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("AzuraParticle4"), 1, Vector2D(_bodyPos.getX() + _game->random(-20, 20), _bodyPos.getY() + _game->random(-10, 10)), 5, _game->random(0, 360), 2000, 1);
				ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("AzuraParticle5"), 1, Vector2D(_bodyPos.getX() + _game->random(-20, 20), _bodyPos.getY() + _game->random(-10, 10)), 5, _game->random(0, 360), 2000, 1);
			}
			else if(_life3.getLife() > 0)
			{
				ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("AzuraParticle6"), 1,Vector2D(_bodyPos.getX() + _game->random(-20,20), _bodyPos.getY() + 30), 5, _game->random(0, 360), 2000, 1);
				ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("AzuraParticle7"), 1, Vector2D(_bodyPos.getX() + _game->random(-20,20), _bodyPos.getY() + 30), 5, _game->random(0, 360), 2000, 1);
				ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("AzuraParticle8"), 1, Vector2D(_bodyPos.getX() + _game->random(-20,20), _bodyPos.getY() + 30), 5, _game->random(0, 360), 2000, 1);
			}
			_particles = true;
		}
	}
}

void Boss2::manageLife(Life& l, int damage)
{
	l.subLife(damage);
	if (l.getLife() == 0)
	{
		_doSomething = 0;
		_lastFase = _actualFase;
		_actualFase = BetweenFase;
		if (_life2.getLife() > 0)
			_anim->playAnim(AnimatedSpriteComponent::AzuraScream1to2);

		else if(_life3.getLife() > 0)
			_anim->playAnim(AnimatedSpriteComponent::AzuraScream2to3);
	}
}

void Boss2::die()
{
	_anim->die();
	_anim->playAnim(AnimatedSpriteComponent::AzuraDie);
	setDead(true);
	_body->filterCollisions(DEAD_ENEMIES, FLOOR | PLATFORMS);
}