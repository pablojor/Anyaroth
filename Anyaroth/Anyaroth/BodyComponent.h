#pragma once
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include <Box2D/Box2D.h>
#include <string>

class BodyComponent : public PhysicsComponent
{
private:
	b2World* _world = nullptr;
	b2Body* _body = nullptr;
	TransformComponent* _transform = nullptr;
	b2FixtureDef _fixture;
	b2PolygonShape _shape;
	double _textW, _textH, _aX, _aY, _width, _height;

public:
	BodyComponent(GameComponent* obj);
	virtual ~BodyComponent();

	virtual void update();
	inline b2Body* getBody() const { return _body; }
	void setW(double w);
	void setH(double h);

	inline double getW() const { return _width; }
	inline double getH() const { return _height; }

	void addCricleShape(const b2Vec2 &Center, float radius, uint16 ownCategory, uint16 collidesWith);
	void filterCollisions(uint16 ownCategory, uint16 collidesWith, int groupIndex = 0);
	void addFixture(b2FixtureDef* fixture, void* data);
};