#pragma once
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include <Box2D/Box2D.h>

class BodyComponent : public PhysicsComponent
{
private:
	b2World* _world;
	b2Body* _body = nullptr;
	b2FixtureDef _fixture;
	TransformComponent* _transform;
	double _textW, _textH, _aX, _aY, _width, _height;
	b2PolygonShape _shape;

public:
	BodyComponent(GameComponent* obj);
	BodyComponent(GameComponent* obj, Vector2D pos, double height, double width);
	virtual ~BodyComponent();

	virtual void update();
	b2Body* getBody();
	void setW(double w);
	void setH(double h);

	double getW();
	double getH();

	void filterCollisions(uint16 ownCategory, uint16 collidesWith);
};