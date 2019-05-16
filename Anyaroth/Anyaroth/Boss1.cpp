#include "Boss1.h"
#include "Player.h"
#include "BasicRifle.h"
#include "ImprovedRifle.h"
#include "CreditsState.h"
#include "GameManager.h"
#include "CutScene.h"

Boss1::Boss1(Game* g, Player* player, Vector2D pos, BulletPool* pool) : Boss(g, player, pos, pool, g->getTexture("Spenta")), Enemy(g, player, pos, g->getTexture("Spenta"), "boss1Interfase3", "boss1Hit")
{
	_life = 250;
	_life1 = _life2 = _life3 = _life;

	_name = "Spenta Manyu";

	delete(_myGun);
	_myGun = new ImprovedRifle(g);
	_myGun->setMaxCadence(0);
	_myGun->setBulletSpeed(10);
	_myGun->setDamage(3);
	_myGun->setBulletAnimType(BulletAnimType::Default);
	_myGun->setBulletTexture(g->getTexture("SpentaBullet"));

	_bombGun = new BomberGun(g);
	_bombGun->setMaxCadence(0);
	_bombGun->setBulletAnimType(SpentaBomb);
	_bombGun->setBulletTexture(g->getTexture("Bomb"));
	_bombGun->setDamage(8);

	_orbGun = new BossOrbCannon(g);
	_orbGun->setMaxCadence(0);
	_orbGun->setBulletAnimType(BulletAnimType::SpentaOrb);
	_orbGun->setBulletTexture(g->getTexture("SpentaOrb"));
	_orbGun->setDamage(10);

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
	
	_melee = new BossSword(g);;
	addChild(_melee);

	_armVision = true;

	_arm->setActive(false); //poner invisible el brazo del boss

	_playerBody = _player->getComponent<BodyComponent>();

	_hurtParticle = _game->getTexture("Blood");
}

Boss1::~Boss1()
{
	delete _bombGun;
	delete _orbGun;
}

void Boss1::update(double deltaTime)
{
	if (_game->getCurrentState()->getCutScene() == nullptr)
	{
		Boss::update(deltaTime);

		if (isDead())
		{
			if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaEndShield)
			{
				_anim->playAnim(AnimatedSpriteComponent::SpentaDie);

				if (GameManager::getInstance()->getCurrentLevel() == LevelManager::BossDemo)
				{
					_game->getCurrentState()->getMainCamera()->fadeOut(3000);
					_game->getCurrentState()->getMainCamera()->onFadeComplete([this](Game* game)
					{
						game->popState();
						game->changeState(new CreditsState(game));
					});
				}
			}

			if (!_finishLevel)
			{
				CutScene* cutscene = new CutScene(_player);
				cutscene->addPopUpEvent(_game->getCurrentState()->getPlayHUD()->getPopUpPanel());
				cutscene->addChangeLevelEvent();
				_game->getCurrentState()->addCutScene(cutscene);
				cutscene->play();

				_player->setMaxLife(_player->getMaxLife() + 50);
				_finishLevel = true;
			}
		}

		if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaEndShield)
		{
			_actualState = Moving;
		}
	}

	if (_anim->animationFinished() && (_anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaEndShield || _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaEndBomb))
	{
		_actualState = Moving;
	}
}

void Boss1::movement(double deltaTime)
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

void Boss1::meleeAttack()
{
	_game->getSoundManager()->playSFX("spentaSword");

	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	int dir = (_bodyPos.getX() >= _playerPos.getX()) ? -1 : 1;
	_melee->meleeAttack(_bodyPos.getX(), _bodyPos.getY(), dir);

	if (dir == -1)
		_anim->playAnim(AnimatedSpriteComponent::SpentaSwordLeft);
	else
		_anim->playAnim(AnimatedSpriteComponent::SpentaSwordRight);

	_armVision = false;
}

void Boss1::checkMelee(double deltaTime)
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
			_doSomething = _game->random(900, 1300);
			_timeOnMelee = 0;
		}
		else
			_timeOnMelee += deltaTime;
	}
}

void Boss1::armShoot(double deltaTime)
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
		_doSomething = _game->random(1200, 1600);
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

void Boss1::bomberAttack(double deltaTime, int t1, int t2)
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
		_doSomething = _game->random(800, 1200);

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
			_timeBeetwenBombs += _game->random(t1, t2);
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
			_doSomething = _game->random(1000, 2500);
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

	if (other->getTag() == "Misil" && isbeetweenFases() && !_player->isDead())
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

		int rand = _game->random(0, 100);

		if (rand > 66)
			_game->getSoundManager()->playSFX("boss1Interfase1");
		else if (rand > 33)
			_game->getSoundManager()->playSFX("boss1Interfase2");
		else
			_game->getSoundManager()->playSFX("boss1Interfase3");
	}
}

void Boss1::fase1(double deltaTime)
{
	if (_actualState != Shooting)
	{
		if (_actualState != Meleeing)
		{
			if (_noAction > _doSomething)
			{
				int random = _game->random(0, 100);

				if (random < 40)
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

void Boss1::fase2(double deltaTime)
{
	if (_actualState != Bombing)
	{
		if (_actualState != Shooting)
		{
			if (_actualState != Meleeing)
			{
				int random = _game->random(0, 100);

				if (random < 20)
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

void Boss1::fase3(double deltaTime)
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
						int random = _game->random(0, 100);

						if (random < 30)
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

void Boss1::beetwenFases(double deltaTime)
{
	bomberAttack(deltaTime, 200, 600);
	_actualState = Bombing;
	checkMelee(deltaTime);

	if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::SpentaStartShield)
		_anim->playAnim(AnimatedSpriteComponent::SpentaLoopShield);
}

void Boss1::changeFase(int nextFase)
{
	Boss::changeFase(nextFase);

	_timeOnBomberAttack = 0;
	_timeBeetwenBombs = 0;
}

void Boss1::throwBomb()
{
	Vector2D helpPos = Vector2D(_game->random(TILES_SIZE * 6, TILES_SIZE * 42), TILES_SIZE * 7);
	_bombGun->enemyShoot(_myBulletPool, helpPos, 90, "EnemyBullet");
}

void Boss1::throwOrb()
{
	Vector2D helpPos = Vector2D(_body->getBody()->GetPosition().x * 8, _body->getBody()->GetPosition().y * 8);
	_orbGun->enemyShoot(_myBulletPool, helpPos, _game->random(80, 180), "EnemyBullet");
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