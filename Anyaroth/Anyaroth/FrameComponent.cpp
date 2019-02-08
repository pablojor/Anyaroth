#include "FrameComponent.h"



FrameComponent::FrameComponent(TransformComponent* trans, Texture* text, int fil, int col) : RenderComponent(), fil(fil), col(col)
{
	_texture = text;
	_transform = trans;
}


FrameComponent::~FrameComponent()
{
}

void FrameComponent::render() const
{
	SDL_Rect destRect;
	destRect.w = _texture->getW() * _transform->getScale().getX();
	destRect.h = _texture->getH() * _transform->getScale().getY();
	destRect.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * destRect.w;
	destRect.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * destRect.h;

	SDL_Point anchor = { _transform->getAnchor().getX() * destRect.w, _transform->getAnchor().getY() * destRect.h };

	_texture->renderFrame(destRect, fil, col, _transform->getRotation(), anchor, (_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
}
void FrameComponent::flip()
{
	_flip = true;
}

void FrameComponent::unFlip()
{
	_flip = false;
}