#include "Enemy.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "CustomAnimatedSpriteComponent.h"
#include "MovingComponent.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"

Enemy::Enemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : _player(player), _play(play), GameObject(g, tag)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(posIni.getX(), posIni.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);
	
	_body->setW(20);
	_body->setH(20);
	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS | MELEE);
	
	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<CustomAnimatedSpriteComponent>();

	_life = Life(50);
	_movement = addComponent<MovingComponent>();
}

void Enemy::setItList(list<GameObject*>::iterator itFR)
{
	_itList = itFR;
}

void Enemy::beginCollision(GameObject * other, b2Contact* contact)
{
	string otherTag = other->getTag();
	if (otherTag == "Bullet")
	{
		int damage = 0;
		damage=dynamic_cast<Bullet*>(other)->getDamage();
		subLife(damage);
	}
}

void Enemy::update(const double& deltaTime)
{
	GameObject::update(deltaTime);
}

void Enemy::die()
{
	_body->filterCollisions(DEAD_ENEMIES, FLOOR);
}

void Enemy::subLife(int damage)
{
	if (!_dead)
	{
		_life.subLife(damage);
		if (_life.dead())
		{
			die();
			_anim->die();
			_anim->playAnim(AnimatedSpriteComponent::EnemyDie);
			_dead = true;
		}
		else
			_anim->hurt();
	}
}

bool Enemy::inCamera()
{
	return _play->getMainCamera()->inCamera(Vector2D(_body->getBody()->GetPosition().x * 8, _body->getBody()->GetPosition().y * 8));
}

bool Enemy::inCameraOnlyX()
{
	return _play->getMainCamera()->inCameraOnlyX(Vector2D(_body->getBody()->GetPosition().x * 8, _body->getBody()->GetPosition().y * 8));
}

void Enemy::enemySpawn(Enemy* newEnemy)
{
	_play->addObject(newEnemy);
}