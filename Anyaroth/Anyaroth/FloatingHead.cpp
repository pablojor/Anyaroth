#include "FloatingHead.h"
#include "Boss3.h"

FloatingHead::FloatingHead(Game* g, Player* player, Vector2D pos, BulletPool* pool, Boss3 * boss) : StaticFlyingEnemy(g, player, pos, pool), Enemy(g, player, pos, g->getTexture("FlyingHead"), "turretDeath", "turretHit", "turretMeleeHit"), _boss(boss)
{
	_life = 80;

	_myGun->setDamage(4);
	_myGun->setMaxCadence(0);
	_myGun->setBulletSpeed(15);

	_anim->reset();
	_anim->addAnim(AnimatedSpriteComponent::HeadIdle, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::HeadAttackStart, 3, false);
	_anim->addAnim(AnimatedSpriteComponent::HeadAttackLoop, 9, true);
	_anim->addAnim(AnimatedSpriteComponent::HeadAttackEnd, 3, false);
	_anim->addAnim(AnimatedSpriteComponent::HeadDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::HeadIdle);
	_arm->getComponent<CustomAnimatedSpriteComponent>()->setVisible(false);
}

void FloatingHead::shooting(double deltaTime)
{
	double angle = 360.0 / (_numOfShoots * 2);

	if (_currentTimer >= 1000)
	{
		for (int i = 0; i < _numOfShoots; i++)
			_myGun->enemyShoot(_myBulletPool, _arm->getPosition(), _changeAngle ? angle * 2 * i : angle * 2 * i + angle, "EnemyBullet");

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

void FloatingHead::update(double deltaTime)
{
	DistanceEnemy::update(deltaTime);

	if (!isStunned() && !isDead() && inCamera())
	{
		if (!_invincibility && _timeShooting <= 6000)
		{
			shooting(deltaTime);
			_timeShooting += deltaTime;
			_shooting = true;

			if (_anim->getCurrentAnim() == AnimatedSpriteComponent::HeadAttackStart && _anim->animationFinished())
				_anim->playAnim(AnimatedSpriteComponent::HeadAttackLoop);
		}
		else if (_shooting)
		{
			_timeShooting = 0;
			_invincibility = true;
			_shooting = false;
			_anim->playAnim(AnimatedSpriteComponent::HeadAttackEnd);
		}

		if (_anim->getCurrentAnim() == AnimatedSpriteComponent::HeadAttackEnd && _anim->animationFinished())
			_anim->playAnim(AnimatedSpriteComponent::HeadIdle);
	}
}

void FloatingHead::subLife(int damage)
{
	if (!isDead() && !_invincibility)
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
	_anim->playAnim(AnimatedSpriteComponent::HeadAttackStart);
}

bool FloatingHead::isInvincible()
{
	if (!isDead())
		return _invincibility;
	else
		return true;
}

void FloatingHead::die()
{
	_anim->die();
	_anim->playAnim(AnimatedSpriteComponent::HeadDie);

	setDead(true);

	_body->filterCollisions(DEAD_ENEMIES, FLOOR | PLATFORMS);

	_game->getSoundManager()->playSFX(_deathSound);
}