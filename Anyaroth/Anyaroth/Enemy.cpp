#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "Coin.h"
#include "AmmoPackage.h"
#include "AidKit.h"

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
	_body->filterCollisions(ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);
	
	_body->getBody()->SetFixedRotation(true);

	_movement = addComponent<MovingComponent>();
	_anim = addComponent<CustomAnimatedSpriteComponent>();

	_life = Life(50);
}

void Enemy::beginCollision(GameObject * other, b2Contact* contact)
{
	if (other->getTag() == "Bullet" || other->getTag() == "Melee")
	{
		int damage = other->getDamage();
		subLife(damage);

		if (other->getTag() == "Melee")
			_dropMelee = true;
		else
			_dropMelee = false;
	}
}

void Enemy::update(const double& deltaTime)
{
	GameObject::update(deltaTime);

	b2Vec2 playerPos = _player->getComponent<BodyComponent>()->getBody()->GetPosition(), enemyPos = _body->getBody()->GetPosition();
	_playerDistance = Vector2D((playerPos.x - enemyPos.x)*M_TO_PIXEL, (playerPos.y - enemyPos.y)*M_TO_PIXEL);

	if (isDead() && _drop)
	{
		_drop = false;
		drop();
	}
}

void Enemy::die()
{
	_anim->die();
	_anim->playAnim(AnimatedSpriteComponent::EnemyDie);
	setDead(true);
	_body->filterCollisions(DEAD_ENEMIES, FLOOR | PLATFORMS);
}

void Enemy::drop()
{
	int rnd = random(0, 100);

	if (rnd < 50 && _dropMelee)
	{
		addChild(new AidKit(_game, Vector2D(_body->getBody()->GetPosition().x*M_TO_PIXEL, _body->getBody()->GetPosition().y*M_TO_PIXEL), _player->getLife().getMaxLife() / 4));
	}
	else if (rnd < 15)
	{
		addChild(new AmmoPackage(_game, Vector2D(_body->getBody()->GetPosition().x*M_TO_PIXEL, _body->getBody()->GetPosition().y*M_TO_PIXEL), 1));
	}
	else if (rnd > 15)
	{
		addChild(new Coin(_game, Vector2D(_body->getBody()->GetPosition().x*M_TO_PIXEL, _body->getBody()->GetPosition().y*M_TO_PIXEL), _coinValue));
	}
}

void Enemy::subLife(int damage)
{
	if (!isDead())
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