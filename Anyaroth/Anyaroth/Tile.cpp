#include "Tile.h"
#include "FrameComponent.h"
#include "TransformComponent.h"
#include "Game.h"
//#include "BoxCollider.h"

Tile::Tile(double x, double y, int c, int f, Texture* t)
{
	addComponent<Texture>(t);
	auto transform = addComponent<TransformComponent>();
	auto frame = addComponent<FrameComponent>();

	//addComponent<BoxCollider>();

	transform->setPosition(x* RESOLUTION, y *RESOLUTION); //el 3 sería el factor de resolución!!
	transform->setScale(3 * RESOLUTION);
	frame->setFilAndCol(f, c);
}
