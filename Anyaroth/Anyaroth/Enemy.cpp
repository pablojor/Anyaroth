#include "Enemy.h"
#include "SpriteComponent.h"


Enemy::Enemy(Texture* texture, Vector2D iniPos) : GameComponent() {

	auto transform = addComponent<TransformComponent>();
	addComponent<SpriteComponent>();

	transform->setPosition(iniPos.getX(), iniPos.getY());

}

Enemy::~Enemy() {
}

void Enemy::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}