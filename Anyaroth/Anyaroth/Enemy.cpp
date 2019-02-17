#include "Enemy.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "MeleeEnemyComponent.h"
#include "MovingComponent.h"
#include "Game.h"
#include "Player.h"

Enemy::Enemy(Texture* texture, Vector2D iniPos, Player* player, Game* g) : GameComponent(g) {

	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(iniPos.getX(), iniPos.getY());

	auto anim = addComponent<AnimatedSpriteComponent>();
	auto playerTrans = addComponent<MeleeEnemyComponent>();
	auto body = addComponent<BodyComponent>();
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

void Enemy::update()
{
	GameComponent::update();
}