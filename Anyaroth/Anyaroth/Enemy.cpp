#include "Enemy.h"
#include "MeleeEnemyComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "BoxCollider.h"
#include "Game.h"
#include "Player.h"

Enemy::Enemy(Texture* texture, Vector2D iniPos, Player* player) : GameComponent() {

	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	auto anim = addComponent<AnimatedSpriteComponent>();
	auto playerTrans = addComponent<MeleeEnemyComponent>();

	addComponent<MovingComponent>();
	addComponent<BoxCollider>();

	playerTrans->addPlayer(player);

	anim->addAnim(AnimatedSpriteComponent::Idle, 16, true);
	anim->addAnim(AnimatedSpriteComponent::Walk, 10, true);
	anim->addAnim(AnimatedSpriteComponent::WalkBack, 10, true); //esta en realidad es opcional
	anim->addAnim(AnimatedSpriteComponent::MeleeKnife, 6, false);

	anim->playAnim(AnimatedSpriteComponent::Idle);

	transform->setPosition(iniPos.getX(), iniPos.getY());

}

Enemy::~Enemy() {
}

void Enemy::update()
{
	GameComponent::update();
}