#pragma once
#include "GameComponent.h"

class ObjectLayer : public GameComponent
{
private:
	vector<Vector2D> _objectsPos;

public:
	ObjectLayer(string filename, string name);

	inline vector<Vector2D> getObjectsPositions() const { return _objectsPos; }
};