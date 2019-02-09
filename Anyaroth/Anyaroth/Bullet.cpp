#include "Bullet.h"
#include "SpriteComponent.h"

Bullet::Bullet(Texture* texture, Vector2D iniPos) : GameComponent() 
{
	auto transform = addComponent<TransformComponent>();
	addComponent<SpriteComponent>();

	transform->setPosition(iniPos.getX(), iniPos.getY());
}

Bullet::~Bullet() 
{

}
