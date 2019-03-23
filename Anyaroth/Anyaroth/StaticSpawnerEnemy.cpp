#include "StaticSpawnerEnemy.h"
#include "GameObject.h"
#include "AnimatedSpriteComponent.h"
#include "Player.h"
#include "FlyingEnemy.h"

StaticSpawnerEnemy::StaticSpawnerEnemy(Player * player, Game * g, PlayState * play, Texture * texture, Vector2D posIni, string tag) : Enemy(g, play, texture, posIni, tag)
{
	_life = 300;
	_vision = 300;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 11, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
	_body->getBody()->SetGravityScale(0);
}

StaticSpawnerEnemy::~StaticSpawnerEnemy()
{
}

void StaticSpawnerEnemy::update(const double& deltaTime)
{
	BodyComponent* _playerBody = _player->getComponent<BodyComponent>();

	b2Vec2 enemyPos = _body->getBody()->GetPosition(), playerPos = _playerBody->getBody()->GetPosition();

	double x = playerPos.x * M_TO_PIXEL - enemyPos.x * M_TO_PIXEL, y = playerPos.y * M_TO_PIXEL - enemyPos.y * M_TO_PIXEL;

	if (!_dead && _activated)
	{
		Enemy::update(deltaTime);
		currentEnemies = activeEnemies();

		if (inCamera())
		{
			if (_time >= _spawnTime && currentEnemies < maxEnemies)
			{
				addChild(new FlyingEnemy(_player, _game, _playstate, _game->getTexture("EnemyMelee"), Vector2D(enemyPos.x * M_TO_PIXEL, enemyPos.y * M_TO_PIXEL), "Enemy"));
				_time = 0;
			}
			else
				_time += deltaTime;
		}
	}
	else
	{
		if (x < _vision && x > -_vision && y < _vision && y > -_vision)
		{
			_activated = true;
			_time = 0;
		}
	}
}

int StaticSpawnerEnemy::activeEnemies()
{
	return getChildren().size();
}