#include "Boss.h"

void Boss::setBossPanel(BossPanel * b)
{
	_bossPanel = b;

	//Actualizamos de primeras el aspecto del Panel del Jugador
	_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
	_bossPanel->setVisible(true);
}

void Boss::update(const double & deltaTime)
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
		_bossPanel->setVisible(false);
}

void Boss::subLife(int damage)
{
	if (!isDead() && !isbeetweenFases())
	{

		if (_life1.getLife() > 0)
		{
			manageLife(_life1, damage);

			if (_life1.getLife() == 0)
				_bossPanel->updateLifeBar(2, _life2.getLife(), _life3.getLife(), _life.getLife());
			else
				_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
		}
		else if (_life2.getLife() > 0)
		{
			manageLife(_life2, damage); 

			if (_life2.getLife() == 0)
				_bossPanel->updateLifeBar(_life1.getLife(), 2, _life3.getLife(), _life.getLife());
			else
				_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
		}
		else if (_life3.getLife() > 0)
		{
			manageLife(_life3, damage);

			if (_life3.getLife() == 0)
				_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), 2, _life.getLife());
			else
				_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
		}
		_spawnParticles = true;
		_anim->hurt();
	}
}

void Boss::manageLife(Life& l, int damage)
{
	l.subLife(damage);

	if (l.getLife() == 0)
	{
		_doSomething = 0;
		_lastFase = _actualFase;
		_actualFase = BetweenFase;
	}
}

void Boss::beginCollision(GameObject * other, b2Contact * contact)
{
	DistanceEnemy::beginCollision(other, contact);
}

void Boss::changeFase(int fase)
{
	_actualFase = fase;
	_armVision = true;
}