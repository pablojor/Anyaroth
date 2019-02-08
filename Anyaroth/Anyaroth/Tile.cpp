#include "Tile.h"
#include "FrameComponent.h"

Tile::Tile(double x, double y, int c, int f, Texture* t) 
{
	transform = new TransformComponent();
	auto a = new FrameComponent(transform, t, c,f);
	addRenderComponent(a);
	transform->setPosition(x, y);
}

Tile::~Tile() {}
