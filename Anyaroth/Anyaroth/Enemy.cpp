#include "Enemy.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "MeleeEnemyComponent.h"
#include "MovingComponent.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"

Enemy::Enemy(Texture* texture, Vector2D iniPos, Player* player, Game* g, string tag) : GameComponent(g, tag)
{
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(iniPos.getX(), iniPos.getY());

	auto body = addComponent<BodyComponent>();

	body->getBody()->SetType(b2_dynamicBody);
	body->getBody()->SetBullet(true);
	body->getBody()->SetFixedRotation(true);
	body->setW(20);
	body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS);

	auto anim = addComponent<AnimatedSpriteComponent>();
	
	auto playerTrans = addComponent<MeleeEnemyComponent>();

	addComponent<MovingComponent>();

	playerTrans->addPlayer(player);

	anim->addAnim(AnimatedSpriteComponent::Idle, 16, true);
	anim->addAnim(AnimatedSpriteComponent::Walk, 10, true);
	anim->addAnim(AnimatedSpriteComponent::WalkBack, 10, true); //esta en realidad es opcional
	anim->addAnim(AnimatedSpriteComponent::MeleeKnife, 6, false);

	anim->playAnim(AnimatedSpriteComponent::Idle);
}

Enemy::~Enemy() 
{
}

void Enemy::beginCollision(GameComponent * other)
{
	string otherTag = other->getTag();
	if (otherTag == "Bullet")
	{
		double damage = 0;
		//damage=dynamic_cast<Bullet*>(other).getDamage();
		subLife(damage);
	}
}

void Enemy::update()
{
	GameComponent::update();
}

void Enemy::setLife(double amount)
{
	_life = amount;
}

void Enemy::addLife(double amount)
{
	_life += amount;
}

void Enemy::subLife(double amount)
{
	if (_life > amount)
		_life -= amount;
	else
		die();
}

void Enemy::die()
{
}
