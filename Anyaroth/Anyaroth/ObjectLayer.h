#pragma once
#include "Vector2D.h"
#include <string>
#include <vector>

using namespace std;

class ObjectLayer
{
private:
	vector<pair<Vector2D, string>> _objectsPos;
	string _name, _data = "";

public:
	ObjectLayer(string filename, string name);

	inline vector<pair<Vector2D, string>> getObjectsData() const { return _objectsPos; }
	inline string getName() { return _name; }
};