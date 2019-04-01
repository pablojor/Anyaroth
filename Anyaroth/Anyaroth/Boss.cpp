#include "Boss.h"

Boss::Boss(Game * g, Player * player, Vector2D pos, BulletPool* pool, Texture* text) : DistanceEnemy(g, player, pos, text, pool), Enemy(g, player, pos, text)
{
	_life = 200;
	_life1 = _life2 = _life3 = _life;
}

Boss::~Boss()
{
}

void Boss::setBossPanel(BossPanel * b)
{
	_bossPanel = b;

	//Actualizamos de primeras el aspecto del Panel del Jugador
	_bossPanel->updateBossName("Spenta Manyu");
	_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
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
}

void Boss::subLife(int damage)
{
	if (!isDead() && !isbeetweenFases())
	{
		if (_life1.getLife() > 0)
			manageLife(_life1, damage);
		else if (_life2.getLife() > 0)
			manageLife(_life2, damage);
		else if (_life3.getLife() > 0)
			manageLife(_life3, damage);

		_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
	}
}

void Boss::manageLife(Life& l, int damage)
{
	l.subLife(damage);
	if (l.getLife()==0)
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
	_actualFase= fase;
	_armVision = true;
}
