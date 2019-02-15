#include "Enemy.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"

Enemy::Enemy(Texture* texture, b2Vec2 iniPos, Game* g) : GameComponent(g) {

	auto body = addComponent<BodyComponent>();
	addComponent<SpriteComponent>();

	body->getBody()->SetTransform(b2Vec2(iniPos.x, iniPos.y), body->getBody()->GetAngle());
}

Enemy::~Enemy() 
{
}

void Enemy::update() {
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
}