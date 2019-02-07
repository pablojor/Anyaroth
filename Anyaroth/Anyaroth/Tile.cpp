#include "Tile.h"
#include "SpriteComponent.h"

Tile::Tile(double x, double y, int c, int f, Texture* t) : col(c), fil(f)
{
	transform = new TransformComponent();
	auto a = new SpriteComponent(transform, t);
	addRenderComponent(a);
	transform->setPosition(x, y);
}

Tile::~Tile() {}

void Tile::render(Uint32 time) {
	for (RenderComponent* rc : renderComp_) {
		rc->renderFrame(fil, col);
	}
}