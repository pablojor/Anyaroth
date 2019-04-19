#include "Boss1.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "BasicRifle.h"
#include "ImprovedRifle.h"

Boss1::Boss1(Game* g, Player* player, Vector2D pos, BulletPool* pool) : Boss(g, player, pos, pool, g->getTexture("Spenta")), Enemy(g, player, pos, g->getTexture("Spenta"))
{
	_life = 700;
	_life1 = _life2 = _life3 = _life;

	delete(_myGun);
	_myGun = new ImprovedRifle(g);
	_myGun->setMaxCadence(0);
	_myGun->setBulletSpeed(8);
	_myGun->setDamage(10);

	_bombGun = new BomberGun(g);
	_bombGun->setMaxCadence(0);
	_bombGun->setBulletAnimType(SpentaBomb);
	_bombGun->setBulletTexture(g->getTexture("Bomb"));
	_bombGun->setDamage(20);

	_orbGun = new BossOrbCannon(g);
	_orbGun->setMaxCadence(0);
	_orbGun->setBulletAnimType(BulletAnimType::SpentaOrb);
	_orbGun->setBulletTexture(g->getTexture("SpentaOrb"));
	_orbGun->setDamage(20);

	_attackRangeX = 120; //No se puede poner mas pequeño que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450

	_anim->addAnim(AnimatedSpriteComponent::SpentaIdle, 20, true);
	_anim->addAnim(AnimatedSpriteComponent::SpentaSwordLeft, 21, false);
	_anim->addAnim(AnimatedSpriteComponent::SpentaSwordRight, 21, false);
	_anim->addAnim(AnimatedSpriteComponent::SpentaStartShield, 17, false);
	_anim->addAnim(AnimatedSpriteComponent::SpentaLoopShield, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::SpentaEndShield, 10, false);
	_anim->addAnim(AnimatedSpriteComponent::SpentaDie, 4, true);
	_anim->addAnim(AnimatedSpriteComponent::SpentaStartBomb, 10, false);
	_anim->addAnim(AnimatedSpriteComponent::SpentaLoopBomb, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::SpentaEndBomb, 10, false);
	_anim->addAnim(AnimatedSpriteComponent::SpentaOrb, 10, false);
	_anim->addAnim(AnimatedSpriteComponent::SpentaWing, 22, false);

	_anim->playAnim(AnimatedSpriteComponent::SpentaIdle);

	_body->setW(40);
	_body->setH(70);
	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE | MISIL);
	_body->getBody()->SetGravityScale(0);

	_originalPos = Vector2D(pos.getX() + (_anim->getTexture()->getW() / 2) / _anim->getTexture()->getNumCols(), pos.getY() + (_anim->getTexture()->getW() / 2) / _anim->getTexture()->getNumCols());
	_melee = new Axe(g, { 100, 0 }, PLAYER, 15, 50, 50, 270);
	addChild(_melee);

	_armVision = true;

	_arm->setActive(false); //poner invisible el brazo del boss

	_playerBody = _player->getComponent<BodyComponent>();
}

Boss1::~Boss1()
{
	delete _bombGun;
	delete _orbGun;
}

void Boss1::update(const double& deltaTime)
{
	Boss::update(deltaTime);
	if (isDead())
	{
		if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaEndShield)
		{
			_anim->playAnim(AnimatedSpriteComponent::SpentaDie);
		}
	}

	if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaEndShield)
	{
		_actualState = Moving;
	}

	if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaEndBomb)
	{
		_actualState = Moving;
	}
	else
	{
		if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaEndShield)
		{
			_anim->playAnim(AnimatedSpriteComponent::SpentaDie);
		}
	}

	if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaEndShield)
	{
		_actualState = Moving;
	}

	if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaEndBomb)
	{
		_actualState = Moving;
	}
}

void Boss1::movement(const double& deltaTime)
{
	if (_actualState == Moving)
	{
		_anim->playAnim(AnimatedSpriteComponent::SpentaIdle);

		if (((_bodyPos.getX() + (_anim->getTexture()->getW() / 2) / _anim->getTexture()->getNumCols() > _originalPos.getX() + _amplitude.getX()) && _dir.getX() == 1) || ((_bodyPos.getX() + (_anim->getTexture()->getW() / 2) / _anim->getTexture()->getNumCols() < _originalPos.getX() - _amplitude.getX()) && _dir.getX() == -1))
			_dir = Vector2D(-_dir.getX(), _dir.getY());

		_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
		_playerPos = Vector2D(_playerBody->getBody()->GetPosition().x * M_TO_PIXEL, _playerBody->getBody()->GetPosition().y * M_TO_PIXEL);

		//Onda Sinusoidal vertical 
		double x = _bodyPos.getX() + _velocity.getX() *_dir.getX();
		double y = _originalPos.getY() + _amplitude.getY() * sin(_k * x - _angularFrequency * deltaTime / 1000);

		_body->getBody()->SetTransform(b2Vec2(x / M_TO_PIXEL, y / M_TO_PIXEL), 0);
	}
}

void Boss1::bomberAttack(const double& deltaTime, int t1, int t2)
{
	if (_actualFase != BetweenFase)
	{
		if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaStartBomb)
			_anim->playAnim(AnimatedSpriteComponent::SpentaLoopBomb);
	}

	_timeOnBomberAttack += deltaTime;
	_armVision = false;

	if (_timeOnBomberAttack >= _bomberAttackTime)
	{
		_timeOnBomberAttack = 0;
		_timeBeetwenBombs = 0;
		_armVision = true;
		_doSomething = random(800, 1200);

		if (_actualFase != BetweenFase)
		{
			_anim->playAnim(AnimatedSpriteComponent::SpentaEndBomb);
		}
	}
	else
	{
		if (_timeOnBomberAttack >= _timeBeetwenBombs)
		{
			throwBomb();
			_timeBeetwenBombs += random(t1, t2);
		}
	}
}

void Boss1::meleeAttack()
{
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	int dir = (_bodyPos.getX() >= _playerPos.getX()) ? -1 : 1;
	_melee->meleeAttack(_bodyPos.getX(), _bodyPos.getY(), dir);

	if (dir == -1)
		_anim->playAnim(AnimatedSpriteComponent::SpentaSwordLeft);
	else
		_anim->playAnim(AnimatedSpriteComponent::SpentaSwordRight);

	_armVision = false;
}

void Boss1::checkMelee(const double& deltaTime)
{
	if (_melee != nullptr && _melee->isActive())
	{
		if (_timeOnMelee > _timeMelee)
		{
			_melee->endMelee();
			if (_actualFase != BetweenFase)
			{
				_anim->playAnim(AnimatedSpriteComponent::SpentaIdle);
				_actualState = Moving;
			}

			_armVision = true;;
			_doSomething = random(900, 1300);
			_timeOnMelee = 0;
		}
		else
			_timeOnMelee += deltaTime;
	}
}

void Boss1::armShoot(const double& deltaTime)
{
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_dirB = (_bodyPos.getX() >= _playerPos.getX()) ? -1 : 1;
	_timeOnShooting += deltaTime;
	_armVision = false;

	if (_actualBullet == 0 && !ida)
	{
		_timeOnShooting = 0;
		_actualState = Moving;
		_armVision = true;
		ida = true;
		_timeBeetwenBullets = 50;
		_doSomething = random(1200, 1600);
	}
	else
	{
		if (_actualBullet == 0 && ida)
		{
			_anim->playAnim(AnimatedSpriteComponent::SpentaWing);
			double x = _playerPos.getX() - _bodyPos.getX();
			double y = _playerPos.getY() - _bodyPos.getY();
			_inicialAngle = (atan2(y, x) * 180 / M_PI) - _dirB * _numBullets / 2 * _angleIncrease;

			_angle = _inicialAngle;
			shootBullet();
		}
		else if (_timeOnShooting >= _timeBeetwenBullets)
		{
			shootBullet();
			_timeBeetwenBullets += 50;
		}
	}
}

void Boss1::orbAttack()
{
	if (_anim->animationFinished())
	{
		throwOrb();
		_actualNumOrbs++;

		if (_actualNumOrbs >= _numOrbs)
		{
			_actualNumOrbs = 0;
			_actualState = Moving;
			_anim->playAnim(AnimatedSpriteComponent::SpentaIdle);
			_doSomething = random(1000, 2500);
		}
		else
		{
			_anim->playAnim(AnimatedSpriteComponent::SpentaIdle);
			_anim->playAnim(AnimatedSpriteComponent::SpentaOrb);
		}
	}
}

void Boss1::beginCollision(GameObject * other, b2Contact * contact)
{
	Boss::beginCollision(other, contact);

	if (other->getTag() == "Misil" && isbeetweenFases())
	{
		if (_lastFase == Fase1)
			changeFase(Fase2);
		else if (_lastFase == Fase2)
			changeFase(Fase3);
		else
			die();

		_anim->playAnim(AnimatedSpriteComponent::SpentaEndShield);
		_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
	}
}

void Boss1::manageLife(Life& l, int damage)
{
	l.subLife(damage);
	if (l.getLife() == 0)
	{
		_doSomething = 0;
		_lastFase = _actualFase;
		_actualState = BetweenFase;
		_actualFase = BetweenFase;
		_anim->playAnim(AnimatedSpriteComponent::SpentaStartShield);
	}
}

void Boss1::fase1(const double& deltaTime)
{
	if (_actualState != Shooting)
	{
		if (_actualState != Meleeing)
		{
			if (_noAction > _doSomething)
			{
				int ra = random(0, 100);
				if (ra >= 40)
				{
					_actualState = Meleeing;
					_noAction = 0;
					meleeAttack();
				}
				else
				{
					armShoot(deltaTime);
					_actualState = Shooting;
					_noAction = 0;
				}
			}
			else
				_noAction += deltaTime;
		}
		else
			checkMelee(deltaTime);
	}
	else
		armShoot(deltaTime);
}

void Boss1::fase2(const double& deltaTime)
{
	if (_actualState != Bombing)
	{
		if (_actualState != Shooting)
		{
			if (_actualState != Meleeing)
			{
				int ra = random(0, 100);
				if (ra >= 70)
				{
					if (_noAction > _doSomething)
					{
						_actualState = Bombing;
						bomberAttack(deltaTime, 100, 200);
						_anim->playAnim(AnimatedSpriteComponent::SpentaStartBomb);
						_noAction = 0;
					}
					else
						_noAction += deltaTime;
				}
				else
				{
					_actualState = Moving;
					fase1(deltaTime);
				}
			}
			else
				checkMelee(deltaTime);
		}
		else
			armShoot(deltaTime);
	}
	else
		bomberAttack(deltaTime, 100, 200);
}

void Boss1::fase3(const double& deltaTime)
{
	if (_actualState != Bombing)
	{
		if (_actualState != Shooting)
		{
			if (_actualState != OrbAttacking)
			{
				if (_actualState != Meleeing)
				{
					if (_noAction > _doSomething)
					{
						int ra = random(0, 100);
						if (ra >= 70)
						{
							_anim->playAnim(AnimatedSpriteComponent::SpentaOrb);//Sera animacion de orbAttackd
							_actualState = OrbAttacking;
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
				orbAttack();
		}
		else
			armShoot(deltaTime);
	}
	else
		bomberAttack(deltaTime, 100, 200);
}

void Boss1::beetwenFases(const double& deltaTime)
{
	bomberAttack(deltaTime, 200, 600);
	_actualState = Bombing;
	checkMelee(deltaTime);

	if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaStartShield)
	{
		_anim->playAnim(AnimatedSpriteComponent::SpentaLoopShield);
	}
}

void Boss1::changeFase(int nextFase)
{
	Boss::changeFase(nextFase);

	_timeOnBomberAttack = 0;
	_timeBeetwenBombs = 0;
}

void Boss1::throwBomb()
{
	Vector2D helpPos = Vector2D(random(100, 700 /*Futuro tope por la derecha*/), 100);
	_bombGun->enemyShoot(_myBulletPool, helpPos, 90, "EnemyBullet");
}

void Boss1::throwOrb()
{
	Vector2D helpPos = Vector2D(_body->getBody()->GetPosition().x * 8, _body->getBody()->GetPosition().y * 8);
	_orbGun->enemyShoot(_myBulletPool, helpPos, random(80, 180), "EnemyBullet");
}

void Boss1::shootBullet()
{
	if (ida)
	{
		shoot();
		_angle += _angleIncrease * _dirB;
		_actualBullet++;

		if (_actualBullet == 10)
		{
			ida = false;
			_timeBeetwenBullets += 300;
		}
	}
	else
	{
		_angle -= _angleIncrease * _dirB;
		shoot();
		_actualBullet--;
	}
}

void Boss1::shoot()
{
	_myGun->enemyShoot(_myBulletPool, _bodyPos, _angle, "EnemyBullet");
}