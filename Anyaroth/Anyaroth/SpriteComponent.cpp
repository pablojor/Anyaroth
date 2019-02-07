#include "SpriteComponent.h"

void SpriteComponent::render() const
{
	SDL_Rect destRect;
	destRect.w = _transform->getSize().getX() * _transform->getScale().getX();
	destRect.h = _transform->getSize().getY() * _transform->getScale().getY();
	destRect.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * destRect.w;
	destRect.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * destRect.h;

	SDL_Point anchor = { _transform->getAnchor().getX() * destRect.w, _transform->getAnchor().getY() * destRect.h };

	_texture->render(destRect, _transform->getRotation(), anchor, (_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
}

void SpriteComponent::flip()
{
	_flip = true;
}

void SpriteComponent::unFlip()
{
	_flip = false;
}