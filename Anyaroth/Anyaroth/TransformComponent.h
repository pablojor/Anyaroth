#pragma once
#include "Component.h"
#include "Vector2D.h"

class GameComponent;

class TransformComponent : public Component 
{
	private:
		Vector2D _anchor;
		Vector2D _scale;
		Vector2D _position;
		double _rotation;
		Vector2D _defaultAnchor; //el anchor inicial (necesario en caso de que el anchor cambie en ejecución)

	public:
		TransformComponent(GameComponent* obj);
		~TransformComponent() {}

		void setPosition(double x, double y) { _position = Vector2D(x, y); }
		void setScale(double x, double y) { _scale = Vector2D(x, y); }
		void setScale(double a) { _scale = Vector2D(a, a); }

		void setAnchor(double x, double y) { _anchor = Vector2D(x, y); }
		void setAnchor(double a) { _anchor = Vector2D(a, a); }

		//Métodos para inicializar _anchor y _defaultAnchor a la vez
		void setDefaultAnchor(double x, double y) { _defaultAnchor = Vector2D(x, y); setAnchor(x,  y); }
		void setDefaultAnchor(double a) { _defaultAnchor = Vector2D(a, a); setAnchor(a); }

		void setRotation(double rot) { _rotation = rot; }

		Vector2D getPosition() { return _position; }
		Vector2D getScale() { return _scale; }
		Vector2D getAnchor() { return _anchor; }
		Vector2D getDefaultAnchor() { return _defaultAnchor; }
		double getRotation() { return _rotation; }
};