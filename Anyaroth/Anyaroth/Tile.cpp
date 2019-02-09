#include "Tile.h"
#include "FrameComponent.h"
#include "TransformComponent.h"

Tile::Tile(double x, double y, int c, int f, Texture* t) 
{
	addComponent<Texture>(t);
	auto transform = addComponent<TransformComponent>();
	auto frame = addComponent<FrameComponent>();

	transform->setPosition(x*3, y*3);
	transform->setScale(3);
	frame->setFilAndCol(f, c);
}

Tile::~Tile() {}
