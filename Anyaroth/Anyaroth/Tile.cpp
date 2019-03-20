#include "Tile.h"
#include "FrameComponent.h"
#include "TransformComponent.h"
#include "Game.h"

Tile::Tile(double x, double y, int f, int c, Texture* t, Game* g, string tag) : GameComponent(g, tag)
{
	addComponent<Texture>(t);
	auto transform = addComponent<TransformComponent>();
	auto frame = addComponent<FrameComponent>();
	transform->setPosition(x, y);
	frame->setFilAndCol(f, c);

	setActive(true);
}