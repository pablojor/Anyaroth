#pragma once
#include <list>
#include "GameComponent.h"

class PlayState;

class Collectable : public GameComponent
{
private:
	list<GameComponent*>::iterator _itList;
	PlayState* _play = nullptr;
	int _value = 0;

public:
	Collectable(PlayState* play, Game* g, Texture* texture, Vector2D iniPos, int value, string tag);
	virtual ~Collectable() {}

	void destroy();
	inline void setItList(list<GameComponent*>::iterator itFR) { _itList = itFR; }
	inline virtual int getValue() const { return _value; }
};