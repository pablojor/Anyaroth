#include "FloatingHead.h"
#include "Boss3.h"


FloatingHead::FloatingHead(Game* g, Player* player, Vector2D pos, BulletPool* pool, Boss3 * boss) : StaticFlyingEnemy(g, player, pos, pool), Enemy(g, player, pos, g->getTexture("Turret"), "turretDeath", "turretHit", "turretMeleeHit"),_boss(boss)
{
	_myGun->setDamage(2);
	_myGun->setMaxCadence(0);
	_myGun->setBulletSpeed(30);
	_hurtParticle = g->getTexture("Sparks");
}




FloatingHead::~FloatingHead()
{
}

void FloatingHead::shooting(double deltaTime)
{
	double angle = 360.0 / (_numOfShoots*2);
	if (_currentTimer >= 1000)
	{
		for (int i = 0; i < _numOfShoots; i++)
		{
			_myGun->enemyShoot(_myBulletPool, _arm->getPosition(), _changeAngle ? angle * 2 * i : angle * 2 * i + angle, "EnemyBullet");
		}
		_currentTimer = 0;
		_changeAngle = !_changeAngle;
	}
	else
		_currentTimer += deltaTime;
}

void FloatingHead::setLifePanel(EnemyLifePanel * lifePanel)
{
	_lifePanel = lifePanel;

	//Actualizamos de primeras el aspecto del Panel del Jugador
	_lifePanel->updateLifeBar(_life.getLife(), _life.getMaxLife());
	_lifePanel->setVisible(true);
}

void FloatingHead::update( const double & deltaTime)
{
	DistanceEnemy::update(deltaTime);

	if (!isStunned() && !isDead() && inCamera())
	{
		if (!_invincibility && _timeShooting<=6000)
		{
			shooting(deltaTime);
			_timeShooting += deltaTime;
		}
		else
		{
			_timeShooting = 0;
			_invincibility = true;
		}
	}
}

void FloatingHead::subLife(int damage)
{
	if (!isDead()&& !_invincibility)
	{
		_life.subLife(damage);

		if (_life.getLife() == 0)
		{
			die();
			_lifePanel->removeEnemy(this);
		}
		else
		{
			_anim->hurt();
			_spawnParticles = true;
		}
	}
}

void FloatingHead::turnInvincibilityOff()
{
	_invincibility = false;
}

bool FloatingHead::isInvincible()
{
	if (!isDead())
	{
		return _invincibility;
	}
	else return true;
}
