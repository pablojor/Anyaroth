#include "Boss1.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"


Boss1::Boss1(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool, ExplosiveBulletPool* explosivePool) : DistanceEnemy(player, g, play, texture, posIni, tag, pool)
{
	_myExplosivePool = explosivePool;
	_bombTexture = g->getTexture("PistolBullet");


	_attackRange = 120; //No se puede poner mas pequeño que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);

	_prevPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
}

void Boss1::update(double time)
{
	if (!_dead)
	{
		if (_fase1)
			Fase1(time);
		else if (_fase2)
			Fase2(time);
		else if (_fase3)
			Fase3(time);
		else
			beetwenFases(time);

	}
}
void Boss1::subLife(int damage)
{
	if (!_dead)
	{
		if (_life1.getLife() > 0)
		{
			_hurt->hurt();
			_life1.subLife(damage);
			if (_life1.dead())
			{
				_fase1 = false;
				_beetwenFase = true;
			}
		}
		else if (_life2.getLife() > 0)
		{
			_hurt->hurt();
			_life2.subLife(damage);
			if (_life2.dead())
			{
				_fase2 = false;
				_beetwenFase = true;
			}
		}
		else
		{
			_life3.subLife(damage);
			if (_life3.dead())
			{
				die();
				_hurt->die();
				_anim->playAnim(AnimatedSpriteComponent::EnemyDie);
				_dead = true;

				_fase3 = false;
			}
			else
				_hurt->hurt();
		}
		
	}
}
void Boss1::movement(double time)
{

	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	//Onda Sinusoidal vertical 
	double x = _bodyPos.getX() + _velocity.getX() *_dir.getX();

	double prevY = _prevPos.getY() + _velocity.getY() *_dir.getY();
	_prevPos = Vector2D(x, prevY);

	double y = prevY + _amplitude * sin(_k * x - _angularFrequency * time / 1000);

	_body->getBody()->SetTransform(b2Vec2(x / M_TO_PIXEL, y / M_TO_PIXEL), 0);
}

void Boss1::bomberAttack(double time)
{
	_timeOnBomberAttack += time;
	if (_timeOnBomberAttack >= _bomberAttackTime)
	{
		_bomberAttacking = false;
		_timeOnBomberAttack = 0;
		_timeBeetwenBombs = 0;
	}
	else
	{ 
		if (_timeOnBomberAttack >= _timeBeetwenBombs)
		{
			throwBomb();
			_timeBeetwenBombs += random(200, 400);
		}

	}
}

void Boss1::Fase1(double time)
{
	movement(time);
}
void Boss1::Fase2(double time)
{
	if (!_bomberAttacking)
	{
		int ra = random(0, 100);
		if (ra >= 70)
		{

			_bomberAttacking = true;
			bomberAttack(time);

		}
		else
			Fase1(time);
	}
	else
		bomberAttack(time);
}
void Boss1::Fase3(double time)
{

}

void Boss1::beetwenFases(double time)
{
	bomberAttack(time);
	//En algun momento pone fase1 = ture; fase2 = true; etc
}


void Boss1::throwBomb()
{
	Bullet* b = _myExplosivePool->getUnusedObject();
	Vector2D helpPos = Vector2D(random(0,500 /*Fututo tope por la derecha*/), _body->getBody()->GetPosition().y);
	Vector2D bulletPos = helpPos.rotateAroundPoint(90, helpPos);

	if (b != nullptr)
	{
		b->init(_bombTexture, helpPos, 0, 10, 90, _bombRange, "PistolBullet");
		b->changeFilter();
	}
	else
	{
		Bullet* b2 = _myExplosivePool->addNewBullet();

		b2->init(_bombTexture, helpPos, 0, 10, 90, _bombRange, "PistolBullet");
		b2->changeFilter();
	}
}