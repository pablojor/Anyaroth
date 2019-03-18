#include "Capsule.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"

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

}

void Capsule::update(double time)
{
	Enemy::update(time);
	if (_spawning)
	{
		//if( animacion de spawn terminada)
		b2Vec2 enemyPos = _body->getBody()->GetPosition();

		enemySpawn(new MeleeEnemy(_player, _game, _play, _game->getTexture("EnemyMelee"), Vector2D(enemyPos.x * 8, enemyPos.y * 8), "Enemy"));
		_play->KillObject(_itList);
	}
}
void Capsule::beginCollision(GameComponent * other, b2Contact* contact)
{
	string otherTag = other->getTag();
	if (otherTag == "Suelo")
	{
		_spawning = true;
		//Animacion de spawn
	}
}