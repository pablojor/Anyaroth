#include "SpriteComponent.h"
#include "GameComponent.h"

SpriteComponent::SpriteComponent(GameComponent* obj) : RenderComponent(obj)
{
	_texture = obj->getComponent<Texture>();
	_transform = obj->getComponent<TransformComponent>();
	if (_transform == nullptr) _transform = obj->addComponent<TransformComponent>();
}

SpriteComponent::~SpriteComponent() 
{
}

void SpriteComponent::render() const 
{
	SDL_Rect destRect;
	destRect.w = _texture->getW() * _transform->getScale().getX();
	destRect.h = _texture->getH() * _transform->getScale().getY();
	destRect.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * destRect.w;
	destRect.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * destRect.h;

	SDL_Point anchor = { _transform->getAnchor().getX() * destRect.w, _transform->getAnchor().getY() * destRect.h };

	_texture->render(destRect, _transform->getRotation(), anchor,(_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
}
void SpriteComponent::flip() 
{
	_flip = true;
}

void SpriteComponent::unFlip() 
{
	_flip = false;
}