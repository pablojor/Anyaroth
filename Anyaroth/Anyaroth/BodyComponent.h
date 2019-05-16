#pragma once
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "Box2D/Box2D.h"
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
	BodyComponent(GameObject* obj);
	BodyComponent(GameObject* obj, double x, double y, double w, double h);
	virtual ~BodyComponent();

	virtual void update(double deltaTime);

	inline b2Body* getBody() const { return _body; }

	void setW(double w);
	void setH(double h);

	void setBody(GameObject* obj, double x, double y, double w, double h);

	inline double getW() const { return _width; }
	inline double getH() const { return _height; }

	void deleteBody();

	void moveShape(const b2Vec2 &Center);
	void addCricleShape(const b2Vec2 &Center, float radius, uint16 ownCategory, uint16 collidesWith);
	void filterCollisions(uint16 ownCategory, uint16 collidesWith, int groupIndex = 0);
	void addFixture(b2FixtureDef* fixture, void* data);
};