#pragma once
#include "GameObject.h"
#include "Texture.h"

class Tile : public GameObject
{
public:
	Tile(double x, double y, int f, int c, Texture* t, Game* g, string tag);
	~Tile() {}
};