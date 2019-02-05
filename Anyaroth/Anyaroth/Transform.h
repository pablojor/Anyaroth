#pragma once
#include "Component.h"
#include "Vector2D.h"

class Transform : public Component {
private:
	Vector2D position;
	Vector2D scale;
	Vector2D rotation;
public:
	Transform(GameComponent* _parent);
	~Transform();
	void activate() {}

	Vector2D getPosition();
	Vector2D getScale();
	Vector2D getRotation();

	void setPosition(double x, double y);
	void setScale(double x, double y);
	void setRotation(double x, double y);
};

