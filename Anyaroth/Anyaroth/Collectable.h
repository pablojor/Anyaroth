#pragma once
#include "GameComponent.h"

class Collectable : public GameComponent //Detectar colision con el coleccionable
{
	private:
		int _value = 0;

	public:
		Collectable(Game* g, Texture* texture, Vector2D iniPos, int value, string tag);
		virtual ~Collectable() {}

		virtual int getValue() { return _value; }
};