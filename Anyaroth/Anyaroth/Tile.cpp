#include "Tile.h"
#include "FrameComponent.h"
#include "TransformComponent.h"
#include "Game.h"

Tile::Tile(double x, double y, int f, int c, Texture* t, Game* g) : GameComponent(g)
{
	addComponent<Texture>(t);
	auto transform = addComponent<TransformComponent>();
	auto frame = addComponent<FrameComponent>();
	transform->setPosition(x* RESOLUTION, y *RESOLUTION);
	//body->getBody()->SetTransform(b2Vec2(x* RESOLUTION, y *RESOLUTION), body->getBody()->GetAngle()); //el 3 sería el factor de resolución!!
	transform->setScale(RESOLUTION);
	frame->setFilAndCol(f, c);
}