#include "Enemy.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "MovingComponent.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"

Enemy::Enemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : _playerTransform(player->getComponent<TransformComponent>()), _play(play), GameComponent(g, tag)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(posIni.getX(), posIni.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);
	_body->getBody()->SetFixedRotation(true);
	_body->setW(20);
	_body->setH(40);
	_body->filterCollisions(ENEMIES, FLOOR | PLAYER_BULLETS);

	//auto playerTrans = addComponent<MeleeEnemyComponent>();

	_anim = addComponent<AnimatedSpriteComponent>();

	/*
	_anim->addAnim(AnimatedSpriteComponent::Idle, 16, true);
	_anim->addAnim(AnimatedSpriteComponent::Walk, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::WalkBack, 10, true); //esta en realidad es opcional
	_anim->addAnim(AnimatedSpriteComponent::MeleeKnife, 6, false);

	_anim->playAnim(AnimatedSpriteComponent::Idle);
	*/
	_movement = addComponent<MovingComponent>();
	a = new EnemyArm(getGame()->getTexture("ArmPistol"), this, player, getGame(), _play, { 35,30 });
	addChild(a);
}
void Enemy::setItList(list<GameObject*>::iterator itFR)
{
	_itList = itFR;
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
