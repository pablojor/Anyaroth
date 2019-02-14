#include "Enemy.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"

Enemy::Enemy(Texture* texture, b2Vec2 iniPos) : GameComponent() {

	auto body = addComponent<BodyComponent>();
	addComponent<SpriteComponent>();

	body->getBody()->SetTransform(b2Vec2(iniPos.x, iniPos.y), body->getBodyDef().angle);
}

Enemy::~Enemy() 
{
}

void Enemy::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}