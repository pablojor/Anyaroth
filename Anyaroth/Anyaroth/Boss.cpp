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

void Boss::subLife(int damage)
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

void Boss::manageLife(Life& l, bool& actualFase, int damage)
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

void Boss::beginCollision(GameComponent * other, b2Contact * contact)
{
	DistanceEnemy::beginCollision(other, contact);
}

void Boss::changeFase(bool & nextFase)
{
	_beetwenFase = false;
	nextFase = true;
	_armVision = true;
}
