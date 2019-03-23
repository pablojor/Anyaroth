#include "Boss1.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"


Boss1::Boss1(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag, BulletPool* pool) : DistanceEnemy(player, g, play, texture, posIni, tag, pool)
{
	_vision = 200;
	_attackRange = 120; //No se puede poner mas pequeño que la velocidad
	_attackTime = 1300; //La animacion tarda unos 450
	_life = 50;

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
		if (fase1)
			Fase1(time);
		else if (fase2)
			Fase2(time);
		else
			Fase3(time);
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
void Boss1::Fase1(double time)
{

}
void Boss1::Fase2(double time)
{

}
void Boss1::Fase3(double time)
{

}

void Boss1::beetwenFases(double time)
{

}
