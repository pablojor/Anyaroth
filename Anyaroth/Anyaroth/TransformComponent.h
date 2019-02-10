#pragma once
#include "Component.h"
#include "Vector2D.h"

class GameComponent;

class TransformComponent : public Component 
{
	private:
		Vector2D _anchor;
		Vector2D _position;
		Vector2D _scale;
		double _rotation;

	public:
		TransformComponent(GameComponent* obj);
		~TransformComponent() {}

		void setPosition(double x, double y) { _position = Vector2D(x, y); }

		void setScale(double x, double y) { _scale = Vector2D(x, y); }
		void setScale(double a) { _scale = Vector2D(a, a); }

		void setAnchor(double x, double y) { _anchor = Vector2D(x, y); }
		void setAnchor(double a) { _anchor = Vector2D(a, a); }

		void setRotation(double rot) { _rotation = rot; }

		Vector2D getPosition() { return _position; }
		Vector2D getScale() { return _scale; }
		Vector2D getAnchor() { return _anchor; }
		double getRotation() { return _rotation; }
};

