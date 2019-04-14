#include "SpriteObject.h"



SpriteObject::SpriteObject(Game* g, Texture* texture, Vector2D iniPos) : GameObject(g, "")
{
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(iniPos.getX(), iniPos.getY());

	auto anim = addComponent<AnimatedSpriteComponent>();
	anim->addAnim(AnimatedSpriteComponent::Idle, 4, true);
	anim->playAnim(AnimatedSpriteComponent::Idle);

}


SpriteObject::~SpriteObject()
{
}
