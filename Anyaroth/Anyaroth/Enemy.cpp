#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"

Enemy::Enemy(Game* g, Player* player, Vector2D pos, Texture* texture) : GameObject(g, "Enemy"), _player(player)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(pos.getX(), pos.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);
	
	_body->setW(20);
	_body->setH(20);
	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);
	
	_body->getBody()->SetFixedRotation(true);

	_movement = addComponent<MovingComponent>();
	_anim = addComponent<CustomAnimatedSpriteComponent>();

	_life = Life(50);
}

void Enemy::beginCollision(GameObject * other, b2Contact* contact)
{
	string otherTag = other->getTag();
	if (otherTag == "Bullet")
	{
		int damage = dynamic_cast<Bullet*>(other)->getDamage();
		subLife(damage);
	}
}

void Enemy::update(const double& deltaTime)
{
	GameObject::update(deltaTime);

	b2Vec2 playerPos = _player->getComponent<BodyComponent>()->getBody()->GetPosition(), enemyPos = _body->getBody()->GetPosition();
	_playerDistance = Vector2D((playerPos.x - enemyPos.x)*M_TO_PIXEL, (playerPos.y - enemyPos.y)*M_TO_PIXEL);
}

void Enemy::die()
{
	_anim->die();
	//_anim->playAnim(AnimatedSpriteComponent::EnemyDie); //Los distance enemy crashean
	_dead = true;
	_body->filterCollisions(DEAD_ENEMIES, FLOOR);
}

void Enemy::subLife(int damage)
{
	if (!_dead)
	{
		_life.subLife(damage);

		if (_life.getLife() == 0)
			die();
		else
			_anim->hurt();
	}
}

bool Enemy::inCamera()
{
	return _game->getCurrentState()->getMainCamera()->inCamera(Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL));
}

bool Enemy::inCameraOnlyX()
{
	return _game->getCurrentState()->getMainCamera()->inCameraOnlyX(Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL));
}