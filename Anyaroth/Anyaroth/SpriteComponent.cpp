#include "SpriteComponent.h"



SpriteComponent::SpriteComponent(TransformComponent* trans, TextureComponent* _texture, unsigned int _width, unsigned int _heigth) : RenderComponent() {
	texture = _texture;
	heigth = _heigth;
	width = _width;
	transform = trans;
}


SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::render() const {
	SDL_Rect destRect;
	// De momento solo la posicion y escala
	// Mas tarde se hara la rotacion
	destRect.x = transform->getPosition().getX();
	destRect.y = transform->getPosition().getY();
	destRect.w = width * transform->getScale().getX();
	destRect.h = heigth * transform->getScale().getY();

	texture->render(destRect);
}
