#pragma once
#include "Component.h"
#include "Vector2D.h"

class GameObject;

class TransformComponent : public Component
{
private:
	Vector2D _anchor;
	Vector2D _scale;
	Vector2D _position;
	double _rotation;
	Vector2D _defaultAnchor; //el anchor inicial (necesario en caso de que el anchor cambie en ejecución)

public:
	TransformComponent(GameObject* obj);
	~TransformComponent() {}

	inline void setPosition(double x, double y) { _position = Vector2D(x, y); }
	inline void setPosition(Vector2D pos) { _position = pos; }
	inline void setScale(double x, double y) { _scale = Vector2D(x, y); }
	inline void setScale(double a) { _scale = Vector2D(a, a); }

	inline void setAnchor(double x, double y) { _anchor = Vector2D(x, y); }
	inline void setAnchor(double a) { _anchor = Vector2D(a, a); }

	//Métodos para inicializar _anchor y _defaultAnchor a la vez
	inline void setDefaultAnchor(double x, double y) { _defaultAnchor = Vector2D(x, y); setAnchor(x, y); }
	inline void setDefaultAnchor(double a) { _defaultAnchor = Vector2D(a, a); setAnchor(a); }

	inline void setRotation(double rot) { _rotation = rot; }

	inline Vector2D getPosition() const { return _position; }
	inline Vector2D getScale() const { return _scale; }
	inline Vector2D getAnchor() const { return _anchor; }
	inline Vector2D getDefaultAnchor() const { return _defaultAnchor; }
	inline double getRotation() const { return _rotation; }
};