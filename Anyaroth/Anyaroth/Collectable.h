#pragma once
#include "GameComponent.h"
#include "Game.h"
#include <list>

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