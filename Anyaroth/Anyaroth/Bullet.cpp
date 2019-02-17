#include "Bullet.h"
#include "SpriteComponent.h"
#include "MovingComponent.h"
#include "BoxCollider.h"

Bullet::Bullet(Texture* texture, Vector2D iniPos) : GameComponent() 
{
	addComponent<Texture>(texture);
	auto transform = addComponent<TransformComponent>();
	addComponent<SpriteComponent>();
	addComponent<MovingComponent>();
	addComponent<BoxCollider>();

	transform->setPosition(iniPos.getX(), iniPos.getY());
}

Bullet::~Bullet() 
{

}
