#pragma once
#include "GameComponent.h"
#include "BodyComponent.h"
#include <list>

class Game;

class Collectable : public GameComponent
{
private:
	BodyComponent* _body = nullptr;

	int _value;

public:
	Collectable(Game* g, Texture* texture, Vector2D iniPos, int value, string tag);
	virtual ~Collectable() {}

	inline virtual int getValue() const { return _value; }

	void collect();
};