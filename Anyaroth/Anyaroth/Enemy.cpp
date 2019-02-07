#include "Enemy.h"
#include "SpriteComponent.h"


Enemy::Enemy(Texture* texture, Vector2D posIni) : GameComponent() {

	transform = new TransformComponent();
	addRenderComponent(new SpriteComponent(transform, texture));

	transform->setPosition(posIni.getX(), posIni.getY());
	

}

Enemy::~Enemy() {
}

void Enemy::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}