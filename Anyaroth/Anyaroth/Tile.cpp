#include "Tile.h"
#include "FrameComponent.h"
#include "TransformComponent.h"
//#include "BoxCollider.h"

Tile::Tile(double x, double y, int c, int f, Texture* t) 
{
	addComponent<Texture>(t);
	auto transform = addComponent<TransformComponent>();
	auto frame = addComponent<FrameComponent>();

	//addComponent<BoxCollider>();

	transform->setPosition(x*3, y*3); //el 3 sería el factor de resolución!!
	transform->setScale(3);
	frame->setFilAndCol(f, c);
}

Tile::~Tile() {}
