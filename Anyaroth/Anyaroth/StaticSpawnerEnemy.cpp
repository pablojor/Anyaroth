#include "StaticSpawnerEnemy.h"
#include "FlyingEnemy.h"

StaticSpawnerEnemy::StaticSpawnerEnemy(Game * g, Player * player, Vector2D pos) : Enemy(g, player, pos, g->getTexture("Hive"))
{
	_vision = 500;
	_life = 30;
	_time = 0;

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 9, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 9, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 9, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
}

void StaticSpawnerEnemy::update(const double& deltaTime)
{
	Enemy::update(deltaTime);

	bool inVision = _playerDistance.getX() < _vision && _playerDistance.getX() > -_vision && _playerDistance.getY() < _vision && _playerDistance.getY() > -_vision;

	if (!isDead() && inCamera() && inVision)
	{
		_currentEnemies = activeEnemies();

		if (_time >= _spawnTime && _currentEnemies < _maxEnemies)
		{
			_anim->playAnim(AnimatedSpriteComponent::EnemyDie);
			addChild(new FlyingEnemy(_game, _player, Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL - TILES_SIZE * 2, _body->getBody()->GetPosition().y * M_TO_PIXEL - TILES_SIZE * 2)));
			_time = 0;
		}
		else
			_time += deltaTime;
	}
	else if (isDead())
		destroyAllChildren();
}

int StaticSpawnerEnemy::activeEnemies()
{
	return getChildren().size();
}