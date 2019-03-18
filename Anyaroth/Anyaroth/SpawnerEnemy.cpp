#include "SpawnerEnemy.h"
#include "GameComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"

SpawnerEnemy::SpawnerEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy(player, g, play, texture, posIni, tag)
{
	_attackTime = 2000;
	_life = 300;
	_speed = -8;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	//_anim->addAnim(AnimatedSpriteComponent::EnemySpawn, 11, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	_body->addCricleShape(b2Vec2(0, _body->getH() + _body->getH() / 20), _body->getW() - _body->getW() / 20, ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetGravityScale(0);

}

void SpawnerEnemy::update(double time)
{
	Enemy::update(time);
	BodyComponent* _playerBody = _player->getComponent<BodyComponent>();

	b2Vec2 enemyPos = _body->getBody()->GetPosition(), playerPos = _playerBody->getBody()->GetPosition();

	double x = playerPos.x * 8 - enemyPos.x * 8, y = playerPos.y * 8 - enemyPos.y * 8;

	if (!_dead && _activated)
	{
		_body->getBody()->SetLinearVelocity({ _speed, _body->getBody()->GetLinearVelocity().y });

		if (!inCamera())
		{
			if (x < 0)
				_speed = -8;
			else
				_speed = 8;
		}
	}
	else 
	{
		if (x < _vision && x > -_vision && y < _vision && y > -_vision)
			_activated = true;
	}
}