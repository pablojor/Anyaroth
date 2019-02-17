#include "Tile.h"
#include "FrameComponent.h"
#include "TransformComponent.h"
#include "Game.h"
//#include "BoxCollider.h"

Tile::Tile(double x, double y, int f, int c, Texture* t) : GameComponent()
{
	addComponent<Texture>(t);
	auto transform = addComponent<TransformComponent>();
	auto frame = addComponent<FrameComponent>();


	transform->setPosition(x, y);
	frame->setFilAndCol(f, c);
}
