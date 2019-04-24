#pragma once
#include "GameObject.h"
#include "Game.h"
#include <list>

class Collectable : public GameObject
{
private:
	BodyComponent* _body = nullptr;
	int _value;
	string _pickSound = "pick1";

public:
	Collectable(Game* game, Texture* texture, Vector2D pos, int value, string tag, string sound = "pick1");
	virtual ~Collectable() {}

	virtual void beginCollision(GameObject* other, b2Contact* contact);
	void collect();

	inline virtual int getValue() const { return _value; }
};