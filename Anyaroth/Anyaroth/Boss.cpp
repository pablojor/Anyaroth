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
		checkMelee();
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

		_anim->hurt();

		if (!isbeetweenFases())
			_bossPanel->updateLifeBar(_life1.getLife(), _life2.getLife(), _life3.getLife(), _life.getLife());
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

void Boss::meleeAttack()
{
	//_melee->endMelee();
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	int dir = (_bodyPos.getX() >= _playerPos.getX()) ? -1 : 1;
	_melee->meleeAttack(_bodyPos.getX(), _bodyPos.getY(), dir);
	_anim->playAnim(AnimatedSpriteComponent::EnemyAttack);
	_armVision = false;
}

void Boss::checkMelee()
{
	if (!isMeleeing() && _melee != nullptr && _melee->isActive())
	{
		_melee->endMelee();
		//Provisional
		if (_actualFase != BetweenFase)
		{
			_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
			_actualState = Moving;
			_armVision = true;;

			_doSomething = _game->random(900, 1300);
		}
	}
}