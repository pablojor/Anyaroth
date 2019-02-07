#include "Bullet.h"
#include "SpriteComponent.h"

Bullet::Bullet(Texture* texture,Vector2D iniPos) : GameComponent() {

	transform = new TransformComponent();
	addRenderComponent(new SpriteComponent(transform, texture));

	transform->setPosition(iniPos.getX(), iniPos.getY());

}

Bullet::~Bullet() {
}
