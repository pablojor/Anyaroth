#include "Enemy.h"
#include "IAControllerComponent.h"
#include "MeleeComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "BoxCollider.h"
#include "Game.h"
#include "Player.h"

Enemy::Enemy(Texture* texture, Vector2D iniPos, Player* player) : GameComponent() {

	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	auto anim = addComponent<AnimatedSpriteComponent>();		
	auto playerTrans = addComponent<IAControllerComponent>();

	addComponent<MovingComponent>();
	addComponent<BoxCollider>();
	addComponent<MeleeComponent>();

	playerTrans->addPlayer(player);

	anim->addAnim("Idle", 16);
	anim->addAnim("Walk", 10);
	anim->playAnim("Idle");

	transform->setPosition(iniPos.getX(), iniPos.getY());
	transform->setScale(RESOLUTION);

}

Enemy::~Enemy() {
}

void Enemy::update() 
{
	GameComponent::update();
}