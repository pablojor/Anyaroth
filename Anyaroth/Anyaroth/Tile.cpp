#include "Tile.h"
#include "FrameComponent.h"
#include "TransformComponent.h"
#include "Game.h"

Tile::Tile(double x, double y, int f, int c, Texture* t)
{
	addComponent<Texture>(t);
	auto transform = addComponent<TransformComponent>();
	auto body = addComponent<BodyComponent>();
	auto frame = addComponent<FrameComponent>();

	body->getBody()->SetTransform(b2Vec2(x* RESOLUTION, y *RESOLUTION), body->getBodyDef().angle); //el 3 sería el factor de resolución!!
	transform->setScale(RESOLUTION);
	frame->setFilAndCol(f, c);
}