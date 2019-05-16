#include "Boss.h"

Boss::Boss(Game * g, Player * player, Vector2D pos, BulletPool* pool, Texture* text) : DistanceEnemy(g, player, pos, text, pool), Enemy(g, player, pos, text)
{
	_affectedByExternalForces = false;
}

void Boss::setBossPanel(BossPanel * b)
{
	_bossPanel = b;

	//Actualizamos de primeras el aspecto del Panel del Jugador
	_bossPanel->updateBossName(_name);
	_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
	_bossPanel->setVisible(true);
}

void Boss::update(double deltaTime)
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
	else
		_player->setNoDamage(true);
	
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

void Boss::addSensors()
{
	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 2 / M_TO_PIXEL, b2Vec2(-2, 2), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	fDef.friction = -26;
	_body->addFixture(&fDef, this);

	shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 2 / M_TO_PIXEL, b2Vec2(2, 2), 0);
	fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	fDef.friction = 26;
	_body->addFixture(&fDef, this);
}