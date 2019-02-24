#pragma once
#include <list>
#include "GameComponent.h"

class PlayState;

class Collectable : public GameComponent //Detectar colision con el coleccionable
{
	private:
		list<GameObject*>::iterator _itList;
		PlayState* _play = nullptr;

		int _value = 0;

	public:
		Collectable(PlayState* play, Game* g, Texture* texture, Vector2D iniPos, int value, string tag);
		virtual ~Collectable() {}

		void destroy();
		void setItList(list<GameObject*>::iterator itFR) { _itList = itFR; }
		virtual int getValue() { return _value; }
};