#pragma once
#include "GameComponent.h"

class Collectable : public GameComponent //Detectar colision con el coleccionable
{
	private:
		int _value = 0;
		//BodyComponent* _body = nullptr;

	public:
		Collectable(Texture* texture, Vector2D iniPos, int value);
		virtual ~Collectable() {}

		int getValue() { return _value; }
};

