#include "Enemy.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "MovingComponent.h"
#include "Game.h"
#include "Player.h"

Enemy::Enemy(Player* player, Game* g, Texture* texture, Vector2D posIni, string tag) : _playerTransform(player->getComponent<TransformComponent>()), GameComponent(g, tag)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(posIni.getX(), posIni.getY());

	auto body = addComponent<BodyComponent>();

	body->getBody()->SetType(b2_dynamicBody);
	body->getBody()->SetBullet(true);
	body->getBody()->SetFixedRotation(true);
	body->setW(20);
	body->filterCollisions(ENEMIES, FLOOR);

	auto anim = addComponent<AnimatedSpriteComponent>();
	
	//auto playerTrans = addComponent<MeleeEnemyComponent>();

	addComponent<MovingComponent>();

	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Idle, 16, true);
	_anim->addAnim(AnimatedSpriteComponent::Walk, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::WalkBack, 10, true); //esta en realidad es opcional
	_anim->addAnim(AnimatedSpriteComponent::MeleeKnife, 6, false);

	_anim->playAnim(AnimatedSpriteComponent::Idle);

	_movement = addComponent<MovingComponent>();
}

void Enemy::update()
{
	GameComponent::update();
}