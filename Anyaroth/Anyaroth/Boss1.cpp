#include "Boss1.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "BasicRifle.h"
#include "ImprovedRifle.h"



Boss1::Boss1(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool, ExplosiveBulletPool* explosivePool) : DistanceEnemy(player, g, play, texture, posIni, tag, pool)
{
	_myExplosivePool = explosivePool;
	_bombTexture = g->getTexture("PistolBullet");
	delete(_myGun);
	_myGun = new ImprovedRifle(g);

	_attackRange = 120; //No se puede poner mas pequeño que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE | MISIL);
	_body->getBody()->SetGravityScale(0);

	_originalPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_melee = new Axe(g, { 200,0 }, PLAYER, 20, 25,25, 0);
	addChild(_melee);

	_armVision = true;

	_playerBody = _player->getComponent<BodyComponent>();

	_life = 200;
	_life1 = _life2 = _life3 = _life;
}

void Boss1::setBossPanel(BossPanel * b)
{
	_bossPanel = b;

	//Actualizamos de primeras el aspecto del Panel del Jugador
	_bossPanel->updateBossName("Spenta Manyu");
	_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
}

void Boss1::update(const double& deltaTime)
{
	if (!_dead)
	{
		DistanceEnemy::update(deltaTime);

		movement(deltaTime);
		checkMelee();
		

		if (_fase1)
			Fase1(deltaTime);
		else if (_fase2)
			Fase2(deltaTime);
		else if (_fase3)
			Fase3(deltaTime);
		else
			beetwenFases(deltaTime);


	}
}
void Boss1::manageLife(Life& l, bool& actualFase, int damage)
{
	_hurt->hurt();
	l.subLife(damage);
	if (l.dead())
	{
		actualFase = false;
		_beetwenFase = true;

		_doSomething = 0;
		_lastFase++;
	}
}

void Boss1::subLife(int damage)
{
	if (!_dead && !_beetwenFase)
	{
		if (_life1.getLife() > 0)
			manageLife(_life1, _fase1, damage);
		else if (_life2.getLife() > 0)
			manageLife(_life2, _fase2, damage);
		else if (_life3.getLife() > 0)
			manageLife(_life3, _fase3, damage);

		if (!_beetwenFase)
			_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
	}
}
void Boss1::movement(const double& deltaTime)
{
	if (move)
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
	move = false;
	if (_timeOnBomberAttack >= _bomberAttackTime)
	{
		_bomberAttacking = false;
		_timeOnBomberAttack = 0;
		_timeBeetwenBombs = 0;
		move = true;
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
	move = false;
	_armVision = false;
}

void Boss1::checkMelee()
{
	if (!isMeleeing() && _melee != nullptr && _melee->isActive())
	{
		_melee->endMelee();
		//Provisional
		_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
		move = true;
		_armVision = true;;

		_doSomething = random(400, 1000);
	}
}

void Boss1::armShoot(const double& deltaTime)
{
	//_arm->shoot();
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_dirB = (_bodyPos.getX() >= _playerPos.getX()) ? -1 : 1;
	_timeOnShooting += deltaTime;
	_armVision = false;
	move = false;
	if (_actualBullet == 0 && !ida)
	{
		_shooting = false;
		_timeOnShooting = 0;
		move = true;
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
		throwBomb();
		_actualNumOrbs++;

		if (_actualNumOrbs >= _numOrbs)
		{
			_orbAttacking = false;
			_actualNumOrbs = 0;
		}
		else
			_anim->playAnim(AnimatedSpriteComponent::EnemyDie);//Sera animacion de orbAttack
			
	}

}

void Boss1::beginCollision(GameComponent * other, b2Contact * contact)
{
	DistanceEnemy::beginCollision(other, contact);

	string otherTag = other->getTag();
	

	if ( otherTag == "Misil" && _beetwenFase)
	{
		if (_lastFase == 1)
			changeFase(_fase2);
		else if (_lastFase == 2)
			changeFase(_fase3);
		else
		{
			_beetwenFase = false;
			die();
		}

		_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
	}

}

void Boss1::Fase1(const double& deltaTime)
{
	if (!_shooting)
	{
		if (_noAction > _doSomething)
		{
			int ra = random(0, 100);

			if (ra >= 70 && !isMeleeing())
			{

				meleeAttack();

				_noAction = 0;
			}


			else if (!isMeleeing())
			{
				armShoot(deltaTime);
				_shooting = true;
				//_doSomething = random(400, 800);
				_noAction = 0;
			}
		}
		else
			_noAction += deltaTime;
	}
	else
		armShoot(deltaTime);
}
void Boss1::Fase2(const double& deltaTime)
{
	if (!_bomberAttacking)
	{
		if (!_shooting)
		{
			int ra = random(0, 100);
			if (ra >= 80)
			{

				if (_noAction > _doSomething)
				{
					_bomberAttacking = true;
					bomberAttack(deltaTime, 100, 200);

					_noAction = 0;
				}
				else
					_noAction += deltaTime;
			}
			else
			{
				move = true;
				Fase1(deltaTime);
			}
		}
		else
			armShoot(deltaTime);
	}
	else
		bomberAttack(deltaTime, 100, 200);
}
void Boss1::Fase3(const double& deltaTime)
{
	if (!_bomberAttacking)
	{
		if (!_shooting)
		{
			if (!_orbAttacking)
			{
				int ra = random(0, 100);
				if (ra >= 70)
				{
					_anim->playAnim(AnimatedSpriteComponent::EnemyDie);//Sera animacion de orbAttack
					_orbAttacking = true;
				}
				else
					Fase2(deltaTime);
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
}

void Boss1::changeFase(bool& nextFase)
{
	_beetwenFase = false;
	nextFase = true;
	_armVision = true;

	_bomberAttacking = false;
	_timeOnBomberAttack = 0;
	_timeBeetwenBombs = 0;
}


void Boss1::throwBomb()
{
	Bullet* b = _myExplosivePool->getUnusedObject();
	Vector2D helpPos = Vector2D(random(100,700 /*Fututo tope por la derecha*/), 200);
	Vector2D bulletPos = helpPos.rotateAroundPoint(90, helpPos);

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
	}
}

void Boss1::throwOrb()
{
	Bullet* b = _myExplosivePool->getUnusedObject();
	Vector2D helpPos = Vector2D(random(100, 700 /*Fututo tope por la derecha*/), 200);
	Vector2D bulletPos = helpPos.rotateAroundPoint(90, helpPos);

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
	}
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
	Bullet* b = _myBulletPool->getUnusedObject();
	
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
	}
}


