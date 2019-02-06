#include "SpriteRenderer.h"



SpriteRenderer::SpriteRenderer(GameComponent* _parent, Texture* _texture, unsigned int _width, unsigned int _heigth) : RenderComponent(_parent) {
	texture = _texture;
	heigth = _heigth;
	width = _width;
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::render() const {
	Transform* aux = parent->getTransform();
	SDL_Rect destRect;
	// De momento solo la posicion y escala
	// Mas tarde se hara la rotacion
	destRect.x = aux->getPosition().getX();
	destRect.y = aux->getPosition().getY();
	destRect.w = width * aux->getScale().getX();
	destRect.h = heigth * aux->getScale().getY();

	texture->render(destRect);
}
