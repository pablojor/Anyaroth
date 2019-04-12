#include "Boss2.h"
#include "Poleaxe.h"
#include "BasicShotgun.h"

Boss2::Boss2(Game* g, Player* player, Vector2D pos, BulletPool* pool) : Boss(g, player, pos, pool, g->getTexture("EnemyMelee")), Enemy(g, player, pos, g->getTexture("EnemyMelee"))
{
	_myGun = new BasicShotgun(g);

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);
	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR | PLATFORMS);
	

	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetFixedRotation(true);
	_body->getBody()->SetGravityScale(3.5);
	
	_originalPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	
	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 3 / M_TO_PIXEL, b2Vec2(0, 3), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);

	_armVision = true;

	_playerBody = _player->getComponent<BodyComponent>();

	_lasers = new LaserHandler(g, g->getTexture("Arm"), g->getTexture("ArmUp"), player, 4);
	addChild(_lasers);

	_melee = new Poleaxe(getGame(), { 50,0 }, PLAYER, 5, 15, 5, this);
	addChild(_melee);
}


Boss2::~Boss2()
{
}

void Boss2::Jump()
{
	
		
	_body->getBody()->ApplyLinearImpulseToCenter(b2Vec2(_dir * 300, -300), true);

	b2PolygonShape shape;
	shape.SetAsBox(15 / M_TO_PIXEL, 22 / M_TO_PIXEL, b2Vec2(0, 0), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = MELEE;
	fDef.filter.maskBits = PLAYER;
	fDef.isSensor = true;
	setTag("Melee");
	_body->addFixture(&fDef, this);
	
	_damage = 20;

	_doSomething = _game->random(1500, 2500);
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
		double range = _playerPos.getX() - _body->getBody()->GetPosition().x* M_TO_PIXEL;


		if (_dir == 1)
			_anim->unFlip();
		else
			_anim->flip();

		if (_actualState != Jumping && (range <= -_stopRange || range >= _stopRange))
			_body->getBody()->SetLinearVelocity(b2Vec2(_velocity.getX() * _dir / M_TO_PIXEL, _body->getBody()->GetLinearVelocity().y));
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
	Boss::meleeAttack();
	_velocity = { _velocity.getX() + 20, _velocity.getY() };
}

void Boss2::endJump()
{
	_endJump = false;
	_body->getBody()->DestroyFixture(_body->getBody()->GetFixtureList());
	_player->stunPlayer();
}

void Boss2::checkMelee()
{
	if (!isMeleeing() && _melee != nullptr && _melee->isActive())
	{
		_velocity = { _originalVelocity.getX(), _originalVelocity.getY() };
		_armVision = true;
	}
	//Se llama despues por que si no no entra en la condicion anterior
	Boss::checkMelee();
}

void Boss2::fase1(const double& deltaTime)
{
	if (_actualState != Shooting)
	{
		if (_actualState != Meleeing)
		{
			if (_noAction > _doSomething)
			{
				if(_playerPos.distance(_bodyPos)<=_shootRange)
				{
					_actualState = Shooting;
					_noAction = 0;
				}

				else 
				{
					meleeAttack();
					_actualState = Meleeing;
					_doSomething = _game->random(400, 800);
					_noAction = 0;
					_armVision = false;
				}
			}
			else
				_noAction += deltaTime;
		}
	}
	else
	{
		shoot();
		_actualState = Moving;
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
						Jump();
						_noAction = 0;
					}
					else
						fase2(deltaTime);
				}
				else
					_noAction += deltaTime;
			}
		}
		else
		{
			shoot();
			_actualState = Moving;
		}
	}
}

void Boss2::beetwenFases(const double& deltaTime)
{
	if (_anim->animationFinished())
	{
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
		}
		_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
		_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
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
		_anim->playAnim(AnimatedSpriteComponent::EnemyDie);
	}
}