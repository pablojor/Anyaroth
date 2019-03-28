#include "Boss.h"

Boss::Boss(Player * player, Game * g, PlayState * play, Texture * texture, Vector2D posIni, string tag, BulletPool* pool) : DistanceEnemy(player, g, play, texture, posIni, tag, pool)
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
	if (!_dead)
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
	if (!_dead && !isbeetweenFases())
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
	_hurt->hurt();
	l.subLife(damage);
	if (l.dead())
	{
		_doSomething = 0;
		_lastFase = _actualFase;
		_actualFase = BetweenFase;
	}
}

void Boss::beginCollision(GameComponent * other, b2Contact * contact)
{
	DistanceEnemy::beginCollision(other, contact);
}

void Boss::changeFase(int fase)
{
	_actualFase= fase;
	_armVision = true;
}
