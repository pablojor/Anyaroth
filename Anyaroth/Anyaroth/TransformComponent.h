#pragma once
#include "Component.h"
#include "Vector2D.h"

class TransformComponent : public Component {
private:
	Vector2D anchor;
	Vector2D position;
	Vector2D scale;
	double rotation;
public:
	TransformComponent();
	~TransformComponent();

	Vector2D getAnchor();
	Vector2D getPosition();
	Vector2D getScale();
	double getRotation();

	void setAnchor(double x, double y);
	void setAnchor(double a);
	void setPosition(double x, double y);
	void setScale(double x, double y);
	void setScale(double a);
	void setRotation(double rot);
};

