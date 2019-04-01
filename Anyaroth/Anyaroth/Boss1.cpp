#include "Boss1.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "BasicRifle.h"
#include "ImprovedRifle.h"



Boss1::Boss1(Game* g, Player* player, Vector2D pos, BulletPool* pool) : Boss(g, player, pos, pool), Enemy(g, player, pos, g->getTexture("EnemyMelee"))
{
	/*_myExplosivePool = explosivePool;
	_myBouncingBulletPool = bouncingPool;*/
	_bombTexture = g->getTexture("PistolBullet");
	delete(_myGun);
	_myGun = new ImprovedRifle(g);
	_bombGun = new BomberGun(g);
	_bombGun->setMaxCadence(0);
	_orbGun = new BossOrbCannon(g);
	_orbGun->setMaxCadence(0);

	_attackRangeX = 120; //No se puede poner mas pequeño que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);
	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE | MISIL);
	_body->getBody()->SetGravityScale(0);

	_originalPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_melee = new Axe(g, { 200,0 }, PLAYER, 20, 25,25, 0);
	addChild(_melee);

	_armVision = true;

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
	if (!isDead())
	{
		checkMelee();
	}
}


void Boss1::movement(const double& deltaTime)
{
	if (_actualState == Moving)
	{
		if (((_bodyPos.getX() > _originalPos.getX() + _amplitude.getX()) && _dir.getX() == 1) || ((_bodyPos.getX() < _originalPos.getX() - _amplitude.getX()) && _dir.getX() == -1))
			_dir = Vector2D(-_dir.getX(), _dir.getY());

		_playerPos = Vector2D(_playerBody->getBody()->GetPosition().x * M_TO_PIXEL, _playerBody->getBody()->GetPosition().y * M_TO_PIXEL);
		_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
		//Onda Sinusoidal vertical 
		double x = _bodyPos.getX() + _velocity.getX() *_dir.getX();

		double y = _originalPos.getY() + _amplitude.getY() * sin(_k * x - _angularFrequency * deltaTime / 1000);

		_body->getBody()->SetTransform(b2Vec2(x / M_TO_PIXEL, y / M_TO_PIXEL), 0);
	}
}

void Boss1::bomberAttack(const double& deltaTime, int t1, int t2)
{
	_timeOnBomberAttack += deltaTime;
	_armVision = false;
	if (_timeOnBomberAttack >= _bomberAttackTime)
	{
		_timeOnBomberAttack = 0;
		_timeBeetwenBombs = 0;
		_actualState = Moving;
		_armVision = true;

		_doSomething = random(800, 1200);
	}
	else
	{ 
		if (_timeOnBomberAttack >= _timeBeetwenBombs)
		{
			throwBomb();
			_timeBeetwenBombs += random(t1,t2);
		}

	}
}

void Boss1::meleeAttack()
{
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	int dir = (_bodyPos.getX() >= _playerPos.getX()) ? -1 : 1;
	_melee->meleeAttack(_bodyPos.getX(), _bodyPos.getY(), dir);
	_anim->playAnim(AnimatedSpriteComponent::EnemyAttack);
	_armVision = false;
}

void Boss1::checkMelee()
{
	if (!isMeleeing() && _melee != nullptr && _melee->isActive())
	{
		_melee->endMelee();
		//Provisional
		_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
		_actualState = Moving;
		_armVision = true;;

		_doSomething = random(900, 1300);
	}
}

void Boss1::armShoot(const double& deltaTime)
{
	//_arm->shoot();
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
	else {
		if (_actualBullet == 0 && ida)
		{
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
	

	//_myGun->enemyShoot(_myBulletPool, _bodyPos, !_anim->isFlipped() ? angle : angle + 180, "EnemyBullet");
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
			_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

			_doSomething = random(1000, 2500);
		}
		else
		{
			//Provisional
			_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
			_anim->playAnim(AnimatedSpriteComponent::EnemyDie);//Sera animacion de orbAttack
		}
			
	}

}

void Boss1::beginCollision(GameObject * other, b2Contact * contact)
{
	Boss::beginCollision(other, contact);

	string otherTag = other->getTag();
	
	if ( otherTag == "Misil" && isbeetweenFases())
	{
 		if (_lastFase == Fase1)
			changeFase(Fase2);
		else if (_lastFase == Fase2)
			changeFase(Fase3);
		else
		{
			die();
		}

		_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
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

				if (ra >= 65)
				{
					_actualState = Meleeing;
					_noAction = 0;
					meleeAttack();
				}

				else
				{
					armShoot(deltaTime);
					_actualState = Shooting;
					//_doSomething = random(400, 800);
					_noAction = 0;
				}
			}
			else
				_noAction += deltaTime;
		}
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
							_anim->playAnim(AnimatedSpriteComponent::EnemyDie);//Sera animacion de orbAttackd
							_actualState = OrbAttacking;
						}
						else
							fase2(deltaTime);
					}
					else
						_noAction += deltaTime;
				}
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
}

void Boss1::changeFase(int nextFase)
{
	Boss::changeFase(nextFase);

	_timeOnBomberAttack = 0;
	_timeBeetwenBombs = 0;
}


void Boss1::throwBomb()
{
	Vector2D helpPos = Vector2D(random(100, 700 /*Fututo tope por la derecha*/), 200);
	_bombGun->enemyShoot(_myBulletPool, helpPos, 90, "EnemyBullet");
	//Bullet* b = _myExplosivePool->getUnusedObject();
	//Vector2D helpPos = Vector2D(random(100,700 /*Fututo tope por la derecha*/), 200);
	/*Vector2D bulletPos = helpPos.rotateAroundPoint(90, helpPos);

	if (b != nullptr)
	{
		b->init(_bombTexture, helpPos, 0, 10, 90, _bombRange, "EnemyBullet");
		b->changeFilter();
	}
	else
	{
		Bullet* b2 = _myExplosivePool->addNewBullet();

		b2->init(_bombTexture, helpPos, 0, 10, 90, _bombRange, "EnemyBullet");
		b2->changeFilter();
	}*/
}

void Boss1::throwOrb()
{
	Vector2D helpPos = Vector2D(_body->getBody()->GetPosition().x * 8, _body->getBody()->GetPosition().y * 8);
	_orbGun->enemyShoot(_myBulletPool, helpPos, random(80, 180), "EnemyBullet");
	/*Bullet* b = _myBouncingBulletPool->getUnusedObject();
	Vector2D helpPos = Vector2D(_body->getBody()->GetPosition().x * 8, _body->getBody()->GetPosition().y * 8);

	if (b != nullptr)
	{
		b->init(_game->getTexture("Coin"), helpPos, 20, 10, random(80,180), _bombRange, "EnemyBullet");
		b->changeFilter();
	}
	else
	{
		Bullet* b2 = _myExplosivePool->addNewBullet();

		b->init(_game->getTexture("Coin"), helpPos, 20, 10, random(80, 180), _bombRange, "EnemyBullet");
		b2->changeFilter();
	}*/
}

void Boss1::shootBullet()
{
	if (ida)
	{
		/*_myGun->enemyShoot(_myBulletPool, _bodyPos, !_anim->isFlipped() ? _angle : _angle + 180, "EnemyBullet");*/
		shoot();
		_angle += _angleIncrease* _dirB;
		_actualBullet++;
		if(_actualBullet==10)
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
	/*Bullet* b = _myBulletPool->getUnusedObject();
	
	if (b != nullptr)
	{
		b->init(_game->getTexture("PistolBullet") , _bodyPos, 8, _damage, _angle, 1000, "EnemyBullet");
		b->changeFilter();
	}
	else
	{
		Bullet* b2 = _myBulletPool->addNewBullet();
		b2->init(_game->getTexture("PistolBullet"), _bodyPos, 8, _damage, _angle, 1000, "EnemyBullet");
		b2->changeFilter();
	}*/
}


