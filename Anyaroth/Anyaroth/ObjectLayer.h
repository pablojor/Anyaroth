#pragma once
#include "GameComponent.h"
class ObjectLayer : public GameComponent
{
public:
	ObjectLayer(string filename, string name);
	virtual ~ObjectLayer();

	vector<Vector2D> const getObjectsPositions() { return _objectsPos; };
private:
	vector<Vector2D> _objectsPos;
};



