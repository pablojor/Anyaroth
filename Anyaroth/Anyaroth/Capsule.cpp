#include "Capsule.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "MeleeEnemy.h"

Capsule::Capsule(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy(player, g, play, texture, posIni, tag)
{
	_attackTime = 2000;
	_life = 300;
	_speed = -8;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetGravityScale(1);

	_body->filterCollisions(DEAD_ENEMIES, FLOOR);

	//Sensor del suelo
	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 2 / M_TO_PIXEL, b2Vec2(0, 2.25 /*Dependera del sprite final */), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = PLAYER;
	fDef.filter.maskBits = FLOOR;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);

}

void Capsule::update(double time)
{
	Enemy::update(time);
	if (_spawning)
	{
		//if( animacion de spawn terminada)
		b2Vec2 enemyPos = _body->getBody()->GetPosition();

		enemySpawn(new MeleeEnemy(_player, _game, _play, _game->getTexture("EnemyMelee"), Vector2D(enemyPos.x * 8 - 30/*Numero a ajustar dependiendo del sprite*/, enemyPos.y * 8 - 30/*Numero a ajustar dependiendo del sprite*/), "Enemy"));
		destroy();
	}
}

void Capsule::beginCollision(GameComponent * other, b2Contact* contact)
{
	string otherTag = other->getTag();
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && other->getTag() == "Ground")
		_spawning = true;
}